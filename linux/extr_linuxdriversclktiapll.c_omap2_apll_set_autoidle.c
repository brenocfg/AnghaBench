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
typedef  int u32 ;
struct dpll_data {int autoidle_mask; int /*<<< orphan*/  control_reg; int /*<<< orphan*/  autoidle_reg; } ;
struct clk_hw_omap {struct dpll_data* dpll_data; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int __ffs (int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static void omap2_apll_set_autoidle(struct clk_hw_omap *clk, u32 val)
{
	struct dpll_data *ad = clk->dpll_data;
	u32 v;

	v = ti_clk_ll_ops->clk_readl(&ad->autoidle_reg);
	v &= ~ad->autoidle_mask;
	v |= val << __ffs(ad->autoidle_mask);
	ti_clk_ll_ops->clk_writel(v, &ad->control_reg);
}