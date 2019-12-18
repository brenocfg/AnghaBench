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
struct g12a_ephy_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_PLL_CTL0 ; 
 unsigned int PLL_CTL0_LOCK_DIG ; 
 struct g12a_ephy_pll* g12a_ephy_pll_to_dev (struct clk_hw*) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int g12a_ephy_pll_is_enabled(struct clk_hw *hw)
{
	struct g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	unsigned int val;

	val = readl(pll->base + ETH_PLL_CTL0);

	return (val & PLL_CTL0_LOCK_DIG) ? 1 : 0;
}