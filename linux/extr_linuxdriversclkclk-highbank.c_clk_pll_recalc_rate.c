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
struct hb_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long HB_PLL_DIVF_MASK ; 
 unsigned long HB_PLL_DIVF_SHIFT ; 
 unsigned long HB_PLL_DIVQ_MASK ; 
 unsigned long HB_PLL_DIVQ_SHIFT ; 
 unsigned long HB_PLL_EXT_BYPASS ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 struct hb_clk* to_hb_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pll_recalc_rate(struct clk_hw *hwclk,
					 unsigned long parent_rate)
{
	struct hb_clk *hbclk = to_hb_clk(hwclk);
	unsigned long divf, divq, vco_freq, reg;

	reg = readl(hbclk->reg);
	if (reg & HB_PLL_EXT_BYPASS)
		return parent_rate;

	divf = (reg & HB_PLL_DIVF_MASK) >> HB_PLL_DIVF_SHIFT;
	divq = (reg & HB_PLL_DIVQ_MASK) >> HB_PLL_DIVQ_SHIFT;
	vco_freq = parent_rate * (divf + 1);

	return vco_freq / (1 << divq);
}