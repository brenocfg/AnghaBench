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
struct clk_rate_request {unsigned long rate; unsigned long best_parent_rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long ac100_clkout_round_rate (struct clk_hw*,unsigned long,unsigned long) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 

__attribute__((used)) static int ac100_clkout_determine_rate(struct clk_hw *hw,
				       struct clk_rate_request *req)
{
	struct clk_hw *best_parent;
	unsigned long best = 0;
	int i, num_parents = clk_hw_get_num_parents(hw);

	for (i = 0; i < num_parents; i++) {
		struct clk_hw *parent = clk_hw_get_parent_by_index(hw, i);
		unsigned long tmp, prate;

		/*
		 * The clock has two parents, one is a fixed clock which is
		 * internally registered by the ac100 driver. The other parent
		 * is a clock from the codec side of the chip, which we
		 * properly declare and reference in the devicetree and is
		 * not implemented in any driver right now.
		 * If the clock core looks for the parent of that second
		 * missing clock, it can't find one that is registered and
		 * returns NULL.
		 * So we end up in a situation where clk_hw_get_num_parents
		 * returns the amount of clocks we can be parented to, but
		 * clk_hw_get_parent_by_index will not return the orphan
		 * clocks.
		 * Thus we need to check if the parent exists before
		 * we get the parent rate, so we could use the RTC
		 * without waiting for the codec to be supported.
		 */
		if (!parent)
			continue;

		prate = clk_hw_get_rate(parent);

		tmp = ac100_clkout_round_rate(hw, req->rate, prate);

		if (tmp > req->rate)
			continue;
		if (req->rate - tmp < req->rate - best) {
			best = tmp;
			best_parent = parent;
		}
	}

	if (!best)
		return -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best;
	req->rate = best;

	return 0;
}