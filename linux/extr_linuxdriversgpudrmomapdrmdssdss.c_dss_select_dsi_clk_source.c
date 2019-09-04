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
struct dss_device {int* dsi_clk_source; } ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  DSS_CLK_SRC_FCK 130 
#define  DSS_CLK_SRC_PLL1_2 129 
#define  DSS_CLK_SRC_PLL2_2 128 
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dss_device*,int /*<<< orphan*/ ,int,int,int) ; 

void dss_select_dsi_clk_source(struct dss_device *dss, int dsi_module,
			       enum dss_clk_source clk_src)
{
	int b, pos;

	switch (clk_src) {
	case DSS_CLK_SRC_FCK:
		b = 0;
		break;
	case DSS_CLK_SRC_PLL1_2:
		BUG_ON(dsi_module != 0);
		b = 1;
		break;
	case DSS_CLK_SRC_PLL2_2:
		BUG_ON(dsi_module != 1);
		b = 1;
		break;
	default:
		BUG();
		return;
	}

	pos = dsi_module == 0 ? 1 : 10;
	REG_FLD_MOD(dss, DSS_CONTROL, b, pos, pos);	/* DSIx_CLK_SWITCH */

	dss->dsi_clk_source[dsi_module] = clk_src;
}