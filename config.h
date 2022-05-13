/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {
    "monospace:style=Regular:size=11:antialias=true:hinting=true:hintstyle=1"};
static const char col_grey1[] = "#000000";
static const char col_grey2[] = "#1e1e1e";
static const char col_grey3[] = "#323232";
static const char col_grey4[] = "#ffffff";
static const char col_cyan[] = "#00d3d0";
static const char *colors[][3] = {
    /* _ = {fg, bg, border} */
    [SchemeNorm] = {col_grey4, col_grey1, col_grey2},
    [SchemeSel] = {col_grey4, col_grey3, col_cyan},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* {class, instance, title, tags mask, isfloating, monitor} */
    // {"Gimp", NULL, NULL, 0, 1, -1},
    // {"Firefox", NULL, NULL, 1 << 8, 0, -1},
    {NULL, NULL, NULL, 0, 0, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* {symbol, arrange function} */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
    {"><>", NULL}, /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-i", NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *emacs[] = {"emacs", NULL};
static const char *emacsclient[] = {"emacsclient", "-nc", NULL};

static Key keys[] = {
    /* {modifier, key, function, argument} */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.03}},
    {MODKEY, XK_l, setmfact, {.f = +0.03}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_c, killclient, {0}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_m, setlayout, {.v = &layouts[1]}},
    {MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_x, quit, {0}},
    // custom bindings
    {MODKEY, XK_m, spawn, {.v = emacs}},
    {MODKEY, XK_n, spawn, {.v = emacsclient}},
    {MODKEY, XK_b, spawn, SHCMD("firefox")},
    {MODKEY, XK_v, spawn, SHCMD("clipmenu -i")},
    {0, XK_Print, spawn, SHCMD("screenshot")},
    {0, 0X1008FF02, spawn, SHCMD("brightnessctl -q s +10%")},
    {0, 0X1008FF03, spawn, SHCMD("brightnessctl -q s 10%-")},
    {0, 0x1008FF11, spawn, SHCMD("amixer set Master 10%-")},
    {0, 0x1008FF12, spawn, SHCMD("amixer set Master toggle")},
    {0, 0x1008FF13, spawn, SHCMD("amixer set Master 10%+")},
    {MODKEY | ShiftMask, XK_q, spawn, SHCMD("logout_menu")},
    // patches
    {MODKEY | Mod1Mask, XK_j, inplacerotate, {.i = +1}},
    {MODKEY | Mod1Mask, XK_k, inplacerotate, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, inplacerotate, {.i = +2}},
    {MODKEY | ShiftMask, XK_k, inplacerotate, {.i = -2}},
    {MODKEY | ShiftMask, XK_h, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_l, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    // UNUSED bindings
    // {MODKEY, XK_comma, focusmon, {.i = -1}},
    // {MODKEY, XK_period, focusmon, {.i = +1}},
    // {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    // {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* {click, event mask, button, function argument} */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkWinTitle, 0, Button3, zoom, {0}},
    {ClkStatusText, 0, Button3, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button3, togglefloating, {0}},
    {ClkClientWin, Mod1Mask, Button1, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    // UNUSED bindings
    // {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
};
