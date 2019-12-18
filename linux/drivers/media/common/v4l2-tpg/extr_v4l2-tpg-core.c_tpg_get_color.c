#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tpg_data {int pattern; unsigned int src_width; } ;
typedef  enum tpg_color { ____Placeholder_tpg_color } tpg_color ;

/* Variables and functions */
#define  TPG_COLOR_100_BLACK 170 
#define  TPG_COLOR_100_BLUE 169 
#define  TPG_COLOR_100_CYAN 168 
#define  TPG_COLOR_100_GREEN 167 
#define  TPG_COLOR_100_MAGENTA 166 
#define  TPG_COLOR_100_RED 165 
#define  TPG_COLOR_100_WHITE 164 
#define  TPG_COLOR_100_YELLOW 163 
#define  TPG_COLOR_75_BLUE 162 
#define  TPG_COLOR_75_CYAN 161 
#define  TPG_COLOR_75_GREEN 160 
#define  TPG_COLOR_75_MAGENTA 159 
#define  TPG_COLOR_75_RED 158 
#define  TPG_COLOR_75_YELLOW 157 
#define  TPG_COLOR_CSC_BLACK 156 
#define  TPG_COLOR_CSC_BLUE 155 
#define  TPG_COLOR_CSC_CYAN 154 
#define  TPG_COLOR_CSC_GREEN 153 
#define  TPG_COLOR_CSC_MAGENTA 152 
#define  TPG_COLOR_CSC_RED 151 
#define  TPG_COLOR_CSC_WHITE 150 
#define  TPG_COLOR_CSC_YELLOW 149 
 int /*<<< orphan*/  TPG_COLOR_RAMP ; 
#define  TPG_PAT_100_COLORBAR 148 
#define  TPG_PAT_100_COLORSQUARES 147 
#define  TPG_PAT_100_HCOLORBAR 146 
#define  TPG_PAT_75_COLORBAR 145 
#define  TPG_PAT_ALTERNATING_HLINES 144 
#define  TPG_PAT_ALTERNATING_VLINES 143 
#define  TPG_PAT_BLACK 142 
#define  TPG_PAT_BLUE 141 
#define  TPG_PAT_CHECKERS_16X16 140 
#define  TPG_PAT_CHECKERS_1X1 139 
#define  TPG_PAT_CHECKERS_2X2 138 
#define  TPG_PAT_COLOR_CHECKERS_1X1 137 
#define  TPG_PAT_COLOR_CHECKERS_2X2 136 
#define  TPG_PAT_CROSS_10_PIXELS 135 
#define  TPG_PAT_CROSS_1_PIXEL 134 
#define  TPG_PAT_CROSS_2_PIXELS 133 
#define  TPG_PAT_CSC_COLORBAR 132 
#define  TPG_PAT_GRAY_RAMP 131 
#define  TPG_PAT_GREEN 130 
#define  TPG_PAT_RED 129 
#define  TPG_PAT_WHITE 128 

__attribute__((used)) static enum tpg_color tpg_get_color(const struct tpg_data *tpg,
				    unsigned pat_line, unsigned x)
{
	/* Maximum number of bars are TPG_COLOR_MAX - otherwise, the input print code
	   should be modified */
	static const enum tpg_color bars[3][8] = {
		/* Standard ITU-R 75% color bar sequence */
		{ TPG_COLOR_CSC_WHITE,   TPG_COLOR_75_YELLOW,
		  TPG_COLOR_75_CYAN,     TPG_COLOR_75_GREEN,
		  TPG_COLOR_75_MAGENTA,  TPG_COLOR_75_RED,
		  TPG_COLOR_75_BLUE,     TPG_COLOR_100_BLACK, },
		/* Standard ITU-R 100% color bar sequence */
		{ TPG_COLOR_100_WHITE,   TPG_COLOR_100_YELLOW,
		  TPG_COLOR_100_CYAN,    TPG_COLOR_100_GREEN,
		  TPG_COLOR_100_MAGENTA, TPG_COLOR_100_RED,
		  TPG_COLOR_100_BLUE,    TPG_COLOR_100_BLACK, },
		/* Color bar sequence suitable to test CSC */
		{ TPG_COLOR_CSC_WHITE,   TPG_COLOR_CSC_YELLOW,
		  TPG_COLOR_CSC_CYAN,    TPG_COLOR_CSC_GREEN,
		  TPG_COLOR_CSC_MAGENTA, TPG_COLOR_CSC_RED,
		  TPG_COLOR_CSC_BLUE,    TPG_COLOR_CSC_BLACK, },
	};

	switch (tpg->pattern) {
	case TPG_PAT_75_COLORBAR:
	case TPG_PAT_100_COLORBAR:
	case TPG_PAT_CSC_COLORBAR:
		return bars[tpg->pattern][((x * 8) / tpg->src_width) % 8];
	case TPG_PAT_100_COLORSQUARES:
		return bars[1][(pat_line + (x * 8) / tpg->src_width) % 8];
	case TPG_PAT_100_HCOLORBAR:
		return bars[1][pat_line];
	case TPG_PAT_BLACK:
		return TPG_COLOR_100_BLACK;
	case TPG_PAT_WHITE:
		return TPG_COLOR_100_WHITE;
	case TPG_PAT_RED:
		return TPG_COLOR_100_RED;
	case TPG_PAT_GREEN:
		return TPG_COLOR_100_GREEN;
	case TPG_PAT_BLUE:
		return TPG_COLOR_100_BLUE;
	case TPG_PAT_CHECKERS_16X16:
		return (((x >> 4) & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_BLACK : TPG_COLOR_100_WHITE;
	case TPG_PAT_CHECKERS_1X1:
		return ((x & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	case TPG_PAT_COLOR_CHECKERS_1X1:
		return ((x & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_RED : TPG_COLOR_100_BLUE;
	case TPG_PAT_CHECKERS_2X2:
		return (((x >> 1) & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	case TPG_PAT_COLOR_CHECKERS_2X2:
		return (((x >> 1) & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_RED : TPG_COLOR_100_BLUE;
	case TPG_PAT_ALTERNATING_HLINES:
		return pat_line ? TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	case TPG_PAT_ALTERNATING_VLINES:
		return (x & 1) ? TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	case TPG_PAT_CROSS_1_PIXEL:
		if (pat_line || (x % tpg->src_width) == tpg->src_width / 2)
			return TPG_COLOR_100_BLACK;
		return TPG_COLOR_100_WHITE;
	case TPG_PAT_CROSS_2_PIXELS:
		if (pat_line || ((x % tpg->src_width) + 1) / 2 == tpg->src_width / 4)
			return TPG_COLOR_100_BLACK;
		return TPG_COLOR_100_WHITE;
	case TPG_PAT_CROSS_10_PIXELS:
		if (pat_line || ((x % tpg->src_width) + 10) / 20 == tpg->src_width / 40)
			return TPG_COLOR_100_BLACK;
		return TPG_COLOR_100_WHITE;
	case TPG_PAT_GRAY_RAMP:
		return TPG_COLOR_RAMP + ((x % tpg->src_width) * 256) / tpg->src_width;
	default:
		return TPG_COLOR_100_RED;
	}
}