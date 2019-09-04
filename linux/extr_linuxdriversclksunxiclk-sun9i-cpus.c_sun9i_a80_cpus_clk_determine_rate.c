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
 int CLK_SET_RATE_PARENT ; 
 int EINVAL ; 
 int clk_hw_get_flags (struct clk_hw*) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 
 unsigned long sun9i_a80_cpus_clk_round (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned long) ; 

__attribute__((used)) static int sun9i_a80_cpus_clk_determine_rate(struct clk_hw *clk,
					     struct clk_rate_request *req)
{
	struct clk_hw *parent, *best_parent = NULL;
	int i, num_parents;
	unsigned long parent_rate, best = 0, child_rate, best_child_rate = 0;
	unsigned long rate = req->rate;

	/* find the parent that can help provide the fastest rate <= rate */
	num_parents = clk_hw_get_num_parents(clk);
	for (i = 0; i < num_parents; i++) {
		parent = clk_hw_get_parent_by_index(clk, i);
		if (!parent)
			continue;
		if (clk_hw_get_flags(clk) & CLK_SET_RATE_PARENT)
			parent_rate = clk_hw_round_rate(parent, rate);
		else
			parent_rate = clk_hw_get_rate(parent);

		child_rate = sun9i_a80_cpus_clk_round(rate, NULL, NULL, i,
						      parent_rate);

		if (child_rate <= rate && child_rate > best_child_rate) {
			best_parent = parent;
			best = parent_rate;
			best_child_rate = child_rate;
		}
	}

	if (!best_parent)
		return -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best;
	req->rate = best_child_rate;

	return 0;
}