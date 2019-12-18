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
typedef  enum tpg_color { ____Placeholder_tpg_color } tpg_color ;

/* Variables and functions */
 int TPG_COLOR_100_BLACK ; 
 int TPG_COLOR_100_WHITE ; 
 int TPG_COLOR_CSC_WHITE ; 
#define  TPG_PAT_75_COLORBAR 130 
#define  TPG_PAT_BLACK 129 
#define  TPG_PAT_CSC_COLORBAR 128 

__attribute__((used)) static enum tpg_color tpg_get_textfg_color(struct tpg_data *tpg)
{
	switch (tpg->pattern) {
	case TPG_PAT_75_COLORBAR:
	case TPG_PAT_CSC_COLORBAR:
		return TPG_COLOR_CSC_WHITE;
	case TPG_PAT_BLACK:
		return TPG_COLOR_100_BLACK;
	default:
		return TPG_COLOR_100_WHITE;
	}
}