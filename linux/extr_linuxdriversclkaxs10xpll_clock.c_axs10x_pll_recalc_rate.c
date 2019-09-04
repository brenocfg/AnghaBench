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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct axs10x_pll_clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_REG_FBDIV ; 
 int /*<<< orphan*/  PLL_REG_IDIV ; 
 int /*<<< orphan*/  PLL_REG_ODIV ; 
 unsigned long axs10x_div_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axs10x_pll_read (struct axs10x_pll_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 struct axs10x_pll_clk* to_axs10x_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long axs10x_pll_recalc_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	u64 rate;
	u32 idiv, fbdiv, odiv;
	struct axs10x_pll_clk *clk = to_axs10x_pll_clk(hw);

	idiv = axs10x_div_get_value(axs10x_pll_read(clk, PLL_REG_IDIV));
	fbdiv = axs10x_div_get_value(axs10x_pll_read(clk, PLL_REG_FBDIV));
	odiv = axs10x_div_get_value(axs10x_pll_read(clk, PLL_REG_ODIV));

	rate = (u64)parent_rate * fbdiv;
	do_div(rate, idiv * odiv);

	return rate;
}