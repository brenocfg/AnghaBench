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
typedef  int u64 ;
typedef  int u32 ;
struct clk_pll {scalar_t__ regofs; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SIRFSOC_ABPLL_CTRL0_BYPASS ; 
 int SIRFSOC_ABPLL_CTRL0_SSEN ; 
 scalar_t__ SIRFSOC_CLKC_MEMPLL_AB_CTRL0 ; 
 scalar_t__ SIRFSOC_CLKC_MEMPLL_AB_FREQ ; 
 scalar_t__ SIRFSOC_CLKC_MEMPLL_AB_SSC ; 
 int clkc_readl (scalar_t__) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct clk_pll* to_pllclk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long pll_clk_recalc_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	unsigned long fin = parent_rate;
	struct clk_pll *clk = to_pllclk(hw);
	u64 rate;
	u32 regctrl0 = clkc_readl(clk->regofs + SIRFSOC_CLKC_MEMPLL_AB_CTRL0 -
			SIRFSOC_CLKC_MEMPLL_AB_FREQ);
	u32 regfreq = clkc_readl(clk->regofs);
	u32 regssc = clkc_readl(clk->regofs + SIRFSOC_CLKC_MEMPLL_AB_SSC -
			SIRFSOC_CLKC_MEMPLL_AB_FREQ);
	u32 nr = (regfreq  >> 16 & (BIT(3) - 1)) + 1;
	u32 nf = (regfreq & (BIT(9) - 1)) + 1;
	u32 ssdiv = regssc >> 8 & (BIT(12) - 1);
	u32 ssdepth = regssc >> 20 & (BIT(2) - 1);
	u32 ssmod = regssc & (BIT(8) - 1);

	if (regctrl0 & SIRFSOC_ABPLL_CTRL0_BYPASS)
		return fin;

	if (regctrl0 & SIRFSOC_ABPLL_CTRL0_SSEN) {
		rate = fin;
		rate *= 1 << 24;
		do_div(rate, nr);
		do_div(rate, (256 * ((ssdiv >> ssdepth) << ssdepth)
			+ (ssmod << ssdepth)));
	} else {
		rate = 2 * fin;
		rate *= nf;
		do_div(rate, nr);
	}
	return rate;
}