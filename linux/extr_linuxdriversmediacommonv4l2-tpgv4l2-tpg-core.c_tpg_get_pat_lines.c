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
struct tpg_data {int pattern; } ;

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

__attribute__((used)) static unsigned tpg_get_pat_lines(const struct tpg_data *tpg)
{
	switch (tpg->pattern) {
	case TPG_PAT_CHECKERS_16X16:
	case TPG_PAT_CHECKERS_2X2:
	case TPG_PAT_CHECKERS_1X1:
	case TPG_PAT_COLOR_CHECKERS_2X2:
	case TPG_PAT_COLOR_CHECKERS_1X1:
	case TPG_PAT_ALTERNATING_HLINES:
	case TPG_PAT_CROSS_1_PIXEL:
	case TPG_PAT_CROSS_2_PIXELS:
	case TPG_PAT_CROSS_10_PIXELS:
		return 2;
	case TPG_PAT_100_COLORSQUARES:
	case TPG_PAT_100_HCOLORBAR:
		return 8;
	default:
		return 1;
	}
}