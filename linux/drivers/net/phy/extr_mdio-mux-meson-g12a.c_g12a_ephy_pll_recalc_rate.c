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
typedef  unsigned long u32 ;
struct g12a_ephy_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_PLL_CTL0 ; 
 unsigned long FIELD_GET (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  PLL_CTL0_M ; 
 int /*<<< orphan*/  PLL_CTL0_N ; 
 struct g12a_ephy_pll* g12a_ephy_pll_to_dev (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long g12a_ephy_pll_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	u32 val, m, n;

	val = readl(pll->base + ETH_PLL_CTL0);
	m = FIELD_GET(PLL_CTL0_M, val);
	n = FIELD_GET(PLL_CTL0_N, val);

	return parent_rate * m / n;
}