/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CaskaydiaMono Nerd Font Mono:size=14" };
static const char dmenufont[]       = "CaskaydiaMono Nerd Font Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *    WM_CLASS(STRING) = instance, class
     *    WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 4;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define AltMask Mod1Mask
#define SuperMask Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { SuperMask,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { SuperMask|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { SuperMask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { SuperMask|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *lockcmd[] = { "slimlock", NULL };
static const char *suspendcmd[] = { "suspend.sh", NULL };
static const char *dunstclosecmd[] = { "dunstctl", "close", NULL };
static const char *playerplaypausecmd[] = { "playerctl", "play-pause", NULL };
static const char *playernextcmd[] = { "playerctl", "next", NULL };
static const char *playerpreviouscmd[] = { "playerctl", "previous", NULL };
static const char *toggletransparencycmd[] = { "bash", "-c", "toggle_transparency.sh", NULL };
static const char *switchthemecmd[] = { "bash", "-c", "switch_theme.sh", NULL };
static const char *displaytimecmd[] = { "display-time.sh", NULL };
static const char *repeatcmd[] = { "ydotool_repeat.sh", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { SuperMask,                       XK_p,      spawn,          {.v = dmenucmd } },
    { SuperMask|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { SuperMask,                       XK_b,      togglebar,      {0} },
    { SuperMask,                       XK_j,      focusstack,     {.i = +1 } },
    { SuperMask,                       XK_k,      focusstack,     {.i = -1 } },
    { SuperMask,                       XK_i,      incnmaster,     {.i = +1 } },
    { SuperMask,                       XK_d,      incnmaster,     {.i = -1 } },
    { SuperMask,                       XK_h,      setmfact,       {.f = -0.05} },
    { SuperMask,                       XK_l,      setmfact,       {.f = +0.05} },
    { SuperMask|ShiftMask,             XK_l,      spawn,          {.v = lockcmd} },
    { SuperMask,                       XK_q,      spawn,          {.v = dunstclosecmd} },
    { SuperMask,                       XK_e,      spawn,          {.v = playerplaypausecmd} },
    { SuperMask,                       XK_n,      spawn,          {.v = playernextcmd} },
    { SuperMask,                       XK_m,      spawn,          {.v = playerpreviouscmd} },
    { SuperMask,                       XK_t,      spawn,          {.v = displaytimecmd} },
    { SuperMask,                       XK_Return, zoom,           {0} },
    { SuperMask,                       XK_Tab,    view,           {0} },
    { SuperMask|ShiftMask,             XK_c,      killclient,     {0} },
    { SuperMask,                       XK_space,  setlayout,      {0} },
    { SuperMask|ShiftMask,             XK_space,  togglefloating, {0} },
    { SuperMask|ShiftMask,             XK_space,  spawn,          {.v = toggletransparencycmd} },
    { SuperMask|ShiftMask,             XK_o,      spawn,          {.v = switchthemecmd} },
    { SuperMask,                       XK_0,      view,           {.ui = ~0 } },
    { SuperMask|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { SuperMask,                       XK_comma,  focusmon,       {.i = -1 } },
    { SuperMask,                       XK_period, focusmon,       {.i = +1 } },
    { SuperMask|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { SuperMask|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { SuperMask,                       XK_F4,     spawn,          {.v = repeatcmd} },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { SuperMask|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         SuperMask,         Button1,        movemouse,      {0} },
    { ClkClientWin,         SuperMask,         Button2,        togglefloating, {0} },
    { ClkClientWin,         SuperMask,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            SuperMask,         Button1,        tag,            {0} },
    { ClkTagBar,            SuperMask,         Button3,        toggletag,      {0} },
};
