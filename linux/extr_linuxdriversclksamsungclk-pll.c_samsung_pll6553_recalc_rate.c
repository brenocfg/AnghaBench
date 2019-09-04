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
struct samsung_clk_pll {scalar_t__ con_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL6553_KDIV_MASK ; 
 int PLL6553_KDIV_SHIFT ; 
 int PLL6553_MDIV_MASK ; 
 int PLL6553_MDIV_SHIFT ; 
 int PLL6553_PDIV_MASK ; 
 int PLL6553_PDIV_SHIFT ; 
 int PLL6553_SDIV_MASK ; 
 int PLL6553_SDIV_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct samsung_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long samsung_pll6553_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mdiv, pdiv, sdiv, kdiv, pll_con0, pll_con1;
	u64 fvco = parent_rate;

	pll_con0 = readl_relaxed(pll->con_reg);
	pll_con1 = readl_relaxed(pll->con_reg + 0x4);
	mdiv = (pll_con0 >> PLL6553_MDIV_SHIFT) & PLL6553_MDIV_MASK;
	pdiv = (pll_con0 >> PLL6553_PDIV_SHIFT) & PLL6553_PDIV_MASK;
	sdiv = (pll_con0 >> PLL6553_SDIV_SHIFT) & PLL6553_SDIV_MASK;
	kdiv = (pll_con1 >> PLL6553_KDIV_SHIFT) & PLL6553_KDIV_MASK;

	fvco *= (mdiv << 16) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= 16;

	return (unsigned long)fvco;
}