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
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int __ffs (int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static void _omap3_dpll_write_clken(struct clk_hw_omap *clk, u8 clken_bits)
{
	const struct dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	v = ti_clk_ll_ops->clk_readl(&dd->control_reg);
	v &= ~dd->enable_mask;
	v |= clken_bits << __ffs(dd->enable_mask);
	ti_clk_ll_ops->clk_writel(v, &dd->control_reg);
}