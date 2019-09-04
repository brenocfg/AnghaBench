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
typedef  int s16 ;

/* Variables and functions */
 int PLL2650XX_KDIV_MASK ; 
 int PLL2650XX_MDIV_MASK ; 
 int PLL2650XX_MDIV_SHIFT ; 
 int PLL2650XX_PDIV_MASK ; 
 int PLL2650XX_PDIV_SHIFT ; 
 int PLL2650XX_SDIV_MASK ; 
 int PLL2650XX_SDIV_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct samsung_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long samsung_pll2650xx_recalc_rate(struct clk_hw *hw,
				unsigned long parent_rate)
{
	struct samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mdiv, pdiv, sdiv, pll_con0, pll_con2;
	s16 kdiv;
	u64 fvco = parent_rate;

	pll_con0 = readl_relaxed(pll->con_reg);
	pll_con2 = readl_relaxed(pll->con_reg + 8);
	mdiv = (pll_con0 >> PLL2650XX_MDIV_SHIFT) & PLL2650XX_MDIV_MASK;
	pdiv = (pll_con0 >> PLL2650XX_PDIV_SHIFT) & PLL2650XX_PDIV_MASK;
	sdiv = (pll_con0 >> PLL2650XX_SDIV_SHIFT) & PLL2650XX_SDIV_MASK;
	kdiv = (s16)(pll_con2 & PLL2650XX_KDIV_MASK);

	fvco *= (mdiv << 16) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= 16;

	return (unsigned long)fvco;
}