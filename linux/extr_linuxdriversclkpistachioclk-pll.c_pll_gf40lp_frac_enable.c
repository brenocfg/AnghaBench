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
typedef  int u32 ;
struct pistachio_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CTRL3 ; 
 int /*<<< orphan*/  PLL_CTRL4 ; 
 int PLL_FRAC_CTRL3_FOUT4PHASEPD ; 
 int PLL_FRAC_CTRL3_FOUTPOSTDIVPD ; 
 int PLL_FRAC_CTRL3_FOUTVCOPD ; 
 int PLL_FRAC_CTRL3_PD ; 
 int PLL_FRAC_CTRL4_BYPASS ; 
 int /*<<< orphan*/  pll_lock (struct pistachio_clk_pll*) ; 
 int pll_readl (struct pistachio_clk_pll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_writel (struct pistachio_clk_pll*,int,int /*<<< orphan*/ ) ; 
 struct pistachio_clk_pll* to_pistachio_pll (struct clk_hw*) ; 

__attribute__((used)) static int pll_gf40lp_frac_enable(struct clk_hw *hw)
{
	struct pistachio_clk_pll *pll = to_pistachio_pll(hw);
	u32 val;

	val = pll_readl(pll, PLL_CTRL3);
	val &= ~(PLL_FRAC_CTRL3_PD | PLL_FRAC_CTRL3_FOUTPOSTDIVPD |
		 PLL_FRAC_CTRL3_FOUT4PHASEPD | PLL_FRAC_CTRL3_FOUTVCOPD);
	pll_writel(pll, val, PLL_CTRL3);

	val = pll_readl(pll, PLL_CTRL4);
	val &= ~PLL_FRAC_CTRL4_BYPASS;
	pll_writel(pll, val, PLL_CTRL4);

	pll_lock(pll);

	return 0;
}