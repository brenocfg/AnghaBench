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
typedef  int u32 ;
struct dpll_data {int enable_mask; int /*<<< orphan*/  control_reg; } ;
struct clk_hw_omap {struct dpll_data* dpll_data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int __ffs (int) ; 
 scalar_t__ _omap2_dpll_is_in_bypass (int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

u8 omap2_init_dpll_parent(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 v;
	struct dpll_data *dd;

	dd = clk->dpll_data;
	if (!dd)
		return -EINVAL;

	v = ti_clk_ll_ops->clk_readl(&dd->control_reg);
	v &= dd->enable_mask;
	v >>= __ffs(dd->enable_mask);

	/* Reparent the struct clk in case the dpll is in bypass */
	if (_omap2_dpll_is_in_bypass(v))
		return 1;

	return 0;
}