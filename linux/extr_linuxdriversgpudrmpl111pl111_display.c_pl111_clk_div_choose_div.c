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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP_ULL (unsigned long,int) ; 
 int TIM2_PCD_HI_BITS ; 
 int TIM2_PCD_LO_BITS ; 
 unsigned long abs (unsigned long) ; 
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 

__attribute__((used)) static int pl111_clk_div_choose_div(struct clk_hw *hw, unsigned long rate,
				    unsigned long *prate, bool set_parent)
{
	int best_div = 1, div;
	struct clk_hw *parent = clk_hw_get_parent(hw);
	unsigned long best_prate = 0;
	unsigned long best_diff = ~0ul;
	int max_div = (1 << (TIM2_PCD_LO_BITS + TIM2_PCD_HI_BITS)) - 1;

	for (div = 1; div < max_div; div++) {
		unsigned long this_prate, div_rate, diff;

		if (set_parent)
			this_prate = clk_hw_round_rate(parent, rate * div);
		else
			this_prate = *prate;
		div_rate = DIV_ROUND_UP_ULL(this_prate, div);
		diff = abs(rate - div_rate);

		if (diff < best_diff) {
			best_div = div;
			best_diff = diff;
			best_prate = this_prate;
		}
	}

	*prate = best_prate;
	return best_div;
}