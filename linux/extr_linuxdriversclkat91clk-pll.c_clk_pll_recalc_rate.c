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
struct clk_pll {unsigned long div; int mul; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pll_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);

	if (!pll->div || !pll->mul)
		return 0;

	return (parent_rate / pll->div) * (pll->mul + 1);
}