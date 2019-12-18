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
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
#define  DSS_CLK_SRC_HDMI_PLL 134 
#define  DSS_CLK_SRC_PLL1_1 133 
#define  DSS_CLK_SRC_PLL1_2 132 
#define  DSS_CLK_SRC_PLL1_3 131 
#define  DSS_CLK_SRC_PLL2_1 130 
#define  DSS_CLK_SRC_PLL2_2 129 
#define  DSS_CLK_SRC_PLL2_3 128 

unsigned int dss_pll_get_clkout_idx_for_src(enum dss_clk_source src)
{
	switch (src) {
	case DSS_CLK_SRC_HDMI_PLL:
		return 0;

	case DSS_CLK_SRC_PLL1_1:
	case DSS_CLK_SRC_PLL2_1:
		return 0;

	case DSS_CLK_SRC_PLL1_2:
	case DSS_CLK_SRC_PLL2_2:
		return 1;

	case DSS_CLK_SRC_PLL1_3:
	case DSS_CLK_SRC_PLL2_3:
		return 2;

	default:
		return 0;
	}
}