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
struct davinci_pll_clk {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLLM ; 
 struct davinci_pll_clk* to_davinci_pll_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int davinci_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	u32 mult;

	mult = rate / parent_rate;
	writel(mult - 1, pll->base + PLLM);

	return 0;
}