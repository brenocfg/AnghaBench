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
struct clk_hw_omap {scalar_t__ clkdm; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clkdm_clk_disable ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _omap3_noncore_dpll_stop (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

void omap3_noncore_dpll_disable(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);

	_omap3_noncore_dpll_stop(clk);
	if (clk->clkdm)
		ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
}