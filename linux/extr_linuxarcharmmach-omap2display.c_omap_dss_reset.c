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
struct omap_hwmod_opt_clk {scalar_t__ _clk; } ;
struct omap_hwmod {int opt_clks_cnt; struct omap_hwmod_opt_clk* opt_clks; TYPE_2__* class; } ;
struct TYPE_4__ {TYPE_1__* sysc; } ;
struct TYPE_3__ {int sysc_flags; int /*<<< orphan*/  syss_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  DSS_PLL_CONTROL ; 
 int /*<<< orphan*/  DSS_SDI_CONTROL ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int MAX_MODULE_SOFTRESET_WAIT ; 
 int SYSS_HAS_RESET_STATUS ; 
 int SYSS_RESETDONE_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 scalar_t__ cpu_is_omap3430 () ; 
 int /*<<< orphan*/  dispc_disable_outputs () ; 
 int omap_hwmod_read (struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hwmod_write (int,struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int omap_dss_reset(struct omap_hwmod *oh)
{
	struct omap_hwmod_opt_clk *oc;
	int c = 0;
	int i, r;

	if (!(oh->class->sysc->sysc_flags & SYSS_HAS_RESET_STATUS)) {
		pr_err("dss_core: hwmod data doesn't contain reset data\n");
		return -EINVAL;
	}

	for (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++)
		if (oc->_clk)
			clk_prepare_enable(oc->_clk);

	dispc_disable_outputs();

	/* clear SDI registers */
	if (cpu_is_omap3430()) {
		omap_hwmod_write(0x0, oh, DSS_SDI_CONTROL);
		omap_hwmod_write(0x0, oh, DSS_PLL_CONTROL);
	}

	/*
	 * clear DSS_CONTROL register to switch DSS clock sources to
	 * PRCM clock, if any
	 */
	omap_hwmod_write(0x0, oh, DSS_CONTROL);

	omap_test_timeout((omap_hwmod_read(oh, oh->class->sysc->syss_offs)
				& SYSS_RESETDONE_MASK),
			MAX_MODULE_SOFTRESET_WAIT, c);

	if (c == MAX_MODULE_SOFTRESET_WAIT)
		pr_warn("dss_core: waiting for reset to finish failed\n");
	else
		pr_debug("dss_core: softreset done\n");

	for (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++)
		if (oc->_clk)
			clk_disable_unprepare(oc->_clk);

	r = (c == MAX_MODULE_SOFTRESET_WAIT) ? -ETIMEDOUT : 0;

	return r;
}