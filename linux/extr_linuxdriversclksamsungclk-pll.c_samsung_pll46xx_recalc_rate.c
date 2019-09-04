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
struct samsung_clk_pll {scalar_t__ type; scalar_t__ con_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL1460X_MDIV_MASK ; 
 int PLL4650C_KDIV_MASK ; 
 int PLL46XX_KDIV_MASK ; 
 int PLL46XX_MDIV_MASK ; 
 int PLL46XX_MDIV_SHIFT ; 
 int PLL46XX_PDIV_MASK ; 
 int PLL46XX_PDIV_SHIFT ; 
 int PLL46XX_SDIV_MASK ; 
 int PLL46XX_SDIV_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 scalar_t__ pll_1460x ; 
 scalar_t__ pll_4600 ; 
 scalar_t__ pll_4650c ; 
 int readl_relaxed (scalar_t__) ; 
 struct samsung_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long samsung_pll46xx_recalc_rate(struct clk_hw *hw,
				unsigned long parent_rate)
{
	struct samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mdiv, pdiv, sdiv, kdiv, pll_con0, pll_con1, shift;
	u64 fvco = parent_rate;

	pll_con0 = readl_relaxed(pll->con_reg);
	pll_con1 = readl_relaxed(pll->con_reg + 4);
	mdiv = (pll_con0 >> PLL46XX_MDIV_SHIFT) & ((pll->type == pll_1460x) ?
				PLL1460X_MDIV_MASK : PLL46XX_MDIV_MASK);
	pdiv = (pll_con0 >> PLL46XX_PDIV_SHIFT) & PLL46XX_PDIV_MASK;
	sdiv = (pll_con0 >> PLL46XX_SDIV_SHIFT) & PLL46XX_SDIV_MASK;
	kdiv = pll->type == pll_4650c ? pll_con1 & PLL4650C_KDIV_MASK :
					pll_con1 & PLL46XX_KDIV_MASK;

	shift = ((pll->type == pll_4600) || (pll->type == pll_1460x)) ? 16 : 10;

	fvco *= (mdiv << shift) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= shift;

	return (unsigned long)fvco;
}