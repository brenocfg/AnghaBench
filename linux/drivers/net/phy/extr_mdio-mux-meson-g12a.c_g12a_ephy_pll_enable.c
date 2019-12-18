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
struct g12a_ephy_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_PLL_CTL0 ; 
 int PLL_CTL0_EN ; 
 int PLL_CTL0_LOCK_DIG ; 
 int PLL_CTL0_RST ; 
 int /*<<< orphan*/  PLL_LOCK_TIMEOUT ; 
 struct g12a_ephy_pll* g12a_ephy_pll_to_dev (struct clk_hw*) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int g12a_ephy_pll_enable(struct clk_hw *hw)
{
	struct g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	u32 val = readl(pll->base + ETH_PLL_CTL0);

	/* Apply both enable an reset */
	val |= PLL_CTL0_RST | PLL_CTL0_EN;
	writel(val, pll->base + ETH_PLL_CTL0);

	/* Clear the reset to let PLL lock */
	val &= ~PLL_CTL0_RST;
	writel(val, pll->base + ETH_PLL_CTL0);

	/* Poll on the digital lock instead of the usual analog lock
	 * This is done because bit 31 is unreliable on some SoC. Bit
	 * 31 may indicate that the PLL is not lock eventhough the clock
	 * is actually running
	 */
	return readl_poll_timeout(pll->base + ETH_PLL_CTL0, val,
				  val & PLL_CTL0_LOCK_DIG, 0, PLL_LOCK_TIMEOUT);
}