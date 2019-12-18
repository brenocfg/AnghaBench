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
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;
struct TYPE_2__ {int* dsi_clk_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DSS_CONTROL ; 
#define  OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI 130 
#define  OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI 129 
#define  OMAP_DSS_CLK_SRC_FCK 128 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__ dss ; 

void dss_select_dsi_clk_source(int dsi_module,
		enum omap_dss_clk_source clk_src)
{
	int b, pos;

	switch (clk_src) {
	case OMAP_DSS_CLK_SRC_FCK:
		b = 0;
		break;
	case OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI:
		BUG_ON(dsi_module != 0);
		b = 1;
		break;
	case OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI:
		BUG_ON(dsi_module != 1);
		b = 1;
		break;
	default:
		BUG();
		return;
	}

	pos = dsi_module == 0 ? 1 : 10;
	REG_FLD_MOD(DSS_CONTROL, b, pos, pos);	/* DSIx_CLK_SWITCH */

	dss.dsi_clk_source[dsi_module] = clk_src;
}