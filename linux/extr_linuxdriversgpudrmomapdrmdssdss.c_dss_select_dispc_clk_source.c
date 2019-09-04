#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dss_device {int dispc_clk_source; TYPE_1__* feat; } ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {TYPE_2__ dispc_clk_switch; scalar_t__ has_lcd_clk_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DSS_CLK_SRC_FCK 130 
#define  DSS_CLK_SRC_PLL1_1 129 
#define  DSS_CLK_SRC_PLL2_1 128 
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dss_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void dss_select_dispc_clk_source(struct dss_device *dss,
					enum dss_clk_source clk_src)
{
	int b;

	/*
	 * We always use PRCM clock as the DISPC func clock, except on DSS3,
	 * where we don't have separate DISPC and LCD clock sources.
	 */
	if (WARN_ON(dss->feat->has_lcd_clk_src && clk_src != DSS_CLK_SRC_FCK))
		return;

	switch (clk_src) {
	case DSS_CLK_SRC_FCK:
		b = 0;
		break;
	case DSS_CLK_SRC_PLL1_1:
		b = 1;
		break;
	case DSS_CLK_SRC_PLL2_1:
		b = 2;
		break;
	default:
		BUG();
		return;
	}

	REG_FLD_MOD(dss, DSS_CONTROL, b,		/* DISPC_CLK_SWITCH */
		    dss->feat->dispc_clk_switch.start,
		    dss->feat->dispc_clk_switch.end);

	dss->dispc_clk_source = clk_src;
}