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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LS1X_CLK_PLL_FREQ ; 
 int OSC ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ls1x_pll_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	u32 pll, rate;

	pll = __raw_readl(LS1X_CLK_PLL_FREQ);
	rate = 12 + (pll & GENMASK(5, 0));
	rate *= OSC;
	rate >>= 1;

	return rate;
}