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
typedef  int /*<<< orphan*/  u32 ;
struct g12a_ephy_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_PLL_CTL0 ; 
 int /*<<< orphan*/  PLL_CTL0_EN ; 
 int /*<<< orphan*/  PLL_CTL0_RST ; 
 struct g12a_ephy_pll* g12a_ephy_pll_to_dev (struct clk_hw*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void g12a_ephy_pll_disable(struct clk_hw *hw)
{
	struct g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	u32 val;

	val = readl(pll->base + ETH_PLL_CTL0);
	val &= ~PLL_CTL0_EN;
	val |= PLL_CTL0_RST;
	writel(val, pll->base + ETH_PLL_CTL0);
}