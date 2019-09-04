#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dispc_channel; } ;
struct dpi_data {int dss_model; TYPE_1__ output; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int DSS_CLK_SRC_FCK ; 
 int DSS_CLK_SRC_PLL1_1 ; 
 int DSS_CLK_SRC_PLL2_1 ; 
#define  DSS_MODEL_DRA7 135 
#define  DSS_MODEL_OMAP2 134 
#define  DSS_MODEL_OMAP3 133 
#define  DSS_MODEL_OMAP4 132 
#define  DSS_MODEL_OMAP5 131 
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 
 int dpi_get_clk_src_dra7xx (struct dpi_data*,int) ; 

__attribute__((used)) static enum dss_clk_source dpi_get_clk_src(struct dpi_data *dpi)
{
	enum omap_channel channel = dpi->output.dispc_channel;

	/*
	 * XXX we can't currently use DSI PLL for DPI with OMAP3, as the DSI PLL
	 * would also be used for DISPC fclk. Meaning, when the DPI output is
	 * disabled, DISPC clock will be disabled, and TV out will stop.
	 */
	switch (dpi->dss_model) {
	case DSS_MODEL_OMAP2:
	case DSS_MODEL_OMAP3:
		return DSS_CLK_SRC_FCK;

	case DSS_MODEL_OMAP4:
		switch (channel) {
		case OMAP_DSS_CHANNEL_LCD:
			return DSS_CLK_SRC_PLL1_1;
		case OMAP_DSS_CHANNEL_LCD2:
			return DSS_CLK_SRC_PLL2_1;
		default:
			return DSS_CLK_SRC_FCK;
		}

	case DSS_MODEL_OMAP5:
		switch (channel) {
		case OMAP_DSS_CHANNEL_LCD:
			return DSS_CLK_SRC_PLL1_1;
		case OMAP_DSS_CHANNEL_LCD3:
			return DSS_CLK_SRC_PLL2_1;
		case OMAP_DSS_CHANNEL_LCD2:
		default:
			return DSS_CLK_SRC_FCK;
		}

	case DSS_MODEL_DRA7:
		return dpi_get_clk_src_dra7xx(dpi, channel);

	default:
		return DSS_CLK_SRC_FCK;
	}
}