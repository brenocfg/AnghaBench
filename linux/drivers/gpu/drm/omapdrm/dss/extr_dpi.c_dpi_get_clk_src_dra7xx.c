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
struct dpi_data {int /*<<< orphan*/  dss; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int DSS_CLK_SRC_FCK ; 
 int DSS_CLK_SRC_PLL1_1 ; 
 int DSS_CLK_SRC_PLL1_3 ; 
 int DSS_CLK_SRC_PLL2_1 ; 
 int DSS_CLK_SRC_PLL2_3 ; 
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 
 int /*<<< orphan*/  dss_pll_find_by_src (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum dss_clk_source dpi_get_clk_src_dra7xx(struct dpi_data *dpi,
						  enum omap_channel channel)
{
	/*
	 * Possible clock sources:
	 * LCD1: FCK/PLL1_1/HDMI_PLL
	 * LCD2: FCK/PLL1_3/HDMI_PLL (DRA74x: PLL2_3)
	 * LCD3: FCK/PLL1_3/HDMI_PLL (DRA74x: PLL2_1)
	 */

	switch (channel) {
	case OMAP_DSS_CHANNEL_LCD:
	{
		if (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL1_1))
			return DSS_CLK_SRC_PLL1_1;
		break;
	}
	case OMAP_DSS_CHANNEL_LCD2:
	{
		if (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL1_3))
			return DSS_CLK_SRC_PLL1_3;
		if (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL2_3))
			return DSS_CLK_SRC_PLL2_3;
		break;
	}
	case OMAP_DSS_CHANNEL_LCD3:
	{
		if (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL2_1))
			return DSS_CLK_SRC_PLL2_1;
		if (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL1_3))
			return DSS_CLK_SRC_PLL1_3;
		break;
	}
	default:
		break;
	}

	return DSS_CLK_SRC_FCK;
}