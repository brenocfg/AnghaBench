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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw_omap {int flags; int /*<<< orphan*/  clksel_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clk_writel ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int CLOCK_CLKOUTX2 ; 
 int /*<<< orphan*/  OMAP4430_DPLL_CLKOUTX2_GATE_CTRL_MASK ; 
 int /*<<< orphan*/  OMAP4430_DPLL_CLKOUT_GATE_CTRL_MASK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static void omap4_dpllmx_deny_gatectrl(struct clk_hw_omap *clk)
{
	u32 v;
	u32 mask;

	if (!clk)
		return;

	mask = clk->flags & CLOCK_CLKOUTX2 ?
			OMAP4430_DPLL_CLKOUTX2_GATE_CTRL_MASK :
			OMAP4430_DPLL_CLKOUT_GATE_CTRL_MASK;

	v = ti_clk_ll_ops->clk_readl(&clk->clksel_reg);
	/* Set the bit to deny gatectrl */
	v |= mask;
	ti_clk_ll_ops->clk_writel(v, &clk->clksel_reg);
}