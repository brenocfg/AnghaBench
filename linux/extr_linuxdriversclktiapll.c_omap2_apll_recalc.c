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
struct clk_hw_omap {unsigned long fixed_rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ omap2_apll_is_enabled (struct clk_hw*) ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

__attribute__((used)) static unsigned long omap2_apll_recalc(struct clk_hw *hw,
				       unsigned long parent_rate)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);

	if (omap2_apll_is_enabled(hw))
		return clk->fixed_rate;

	return 0;
}