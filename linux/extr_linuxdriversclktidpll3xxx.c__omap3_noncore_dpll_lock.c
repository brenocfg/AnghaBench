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
typedef  int u8 ;
struct dpll_data {int idlest_mask; int /*<<< orphan*/  idlest_reg; } ;
struct clk_hw_omap {struct dpll_data* dpll_data; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_LOCKED ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  _omap3_dpll_write_clken (struct clk_hw_omap*,int /*<<< orphan*/ ) ; 
 int _omap3_wait_dpll_status (struct clk_hw_omap*,int) ; 
 int /*<<< orphan*/  clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3_dpll_allow_idle (struct clk_hw_omap*) ; 
 int omap3_dpll_autoidle_read (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  omap3_dpll_deny_idle (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static int _omap3_noncore_dpll_lock(struct clk_hw_omap *clk)
{
	const struct dpll_data *dd;
	u8 ai;
	u8 state = 1;
	int r = 0;

	pr_debug("clock: locking DPLL %s\n", clk_hw_get_name(&clk->hw));

	dd = clk->dpll_data;
	state <<= __ffs(dd->idlest_mask);

	/* Check if already locked */
	if ((ti_clk_ll_ops->clk_readl(&dd->idlest_reg) & dd->idlest_mask) ==
	    state)
		goto done;

	ai = omap3_dpll_autoidle_read(clk);

	if (ai)
		omap3_dpll_deny_idle(clk);

	_omap3_dpll_write_clken(clk, DPLL_LOCKED);

	r = _omap3_wait_dpll_status(clk, 1);

	if (ai)
		omap3_dpll_allow_idle(clk);

done:
	return r;
}