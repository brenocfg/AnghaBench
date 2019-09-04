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
typedef  int u32 ;
struct clk_hw_omap {int flags; int enable_bit; scalar_t__ clkdm; int /*<<< orphan*/  enable_reg; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clkdm_clk_disable ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int INVERT_ENABLE ; 
 int TI_CLK_DISABLE_CLKDM_CONTROL ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* ti_clk_get_features () ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

void omap2_dflt_clk_disable(struct clk_hw *hw)
{
	struct clk_hw_omap *clk;
	u32 v;

	clk = to_clk_hw_omap(hw);

	v = ti_clk_ll_ops->clk_readl(&clk->enable_reg);
	if (clk->flags & INVERT_ENABLE)
		v |= (1 << clk->enable_bit);
	else
		v &= ~(1 << clk->enable_bit);
	ti_clk_ll_ops->clk_writel(v, &clk->enable_reg);
	/* No OCP barrier needed here since it is a disable operation */

	if (!(ti_clk_get_features()->flags & TI_CLK_DISABLE_CLKDM_CONTROL) &&
	    clk->clkdm)
		ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
}