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
struct tpg_data {int pattern; unsigned int src_height; } ;

/* Variables and functions */
#define  TPG_PAT_100_COLORSQUARES 138 
#define  TPG_PAT_100_HCOLORBAR 137 
#define  TPG_PAT_ALTERNATING_HLINES 136 
#define  TPG_PAT_CHECKERS_16X16 135 
#define  TPG_PAT_CHECKERS_1X1 134 
#define  TPG_PAT_CHECKERS_2X2 133 
#define  TPG_PAT_COLOR_CHECKERS_1X1 132 
#define  TPG_PAT_COLOR_CHECKERS_2X2 131 
#define  TPG_PAT_CROSS_10_PIXELS 130 
#define  TPG_PAT_CROSS_1_PIXEL 129 
#define  TPG_PAT_CROSS_2_PIXELS 128 

__attribute__((used)) static unsigned tpg_get_pat_line(const struct tpg_data *tpg, unsigned line)
{
	switch (tpg->pattern) {
	case TPG_PAT_CHECKERS_16X16:
		return (line >> 4) & 1;
	case TPG_PAT_CHECKERS_1X1:
	case TPG_PAT_COLOR_CHECKERS_1X1:
	case TPG_PAT_ALTERNATING_HLINES:
		return line & 1;
	case TPG_PAT_CHECKERS_2X2:
	case TPG_PAT_COLOR_CHECKERS_2X2:
		return (line & 2) >> 1;
	case TPG_PAT_100_COLORSQUARES:
	case TPG_PAT_100_HCOLORBAR:
		return (line * 8) / tpg->src_height;
	case TPG_PAT_CROSS_1_PIXEL:
		return line == tpg->src_height / 2;
	case TPG_PAT_CROSS_2_PIXELS:
		return (line + 1) / 2 == tpg->src_height / 4;
	case TPG_PAT_CROSS_10_PIXELS:
		return (line + 10) / 20 == tpg->src_height / 40;
	default:
		return 0;
	}
}