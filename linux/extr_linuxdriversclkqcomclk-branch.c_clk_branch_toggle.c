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
struct clk_branch {int dummy; } ;

/* Variables and functions */
 int clk_branch_wait (struct clk_branch*,int,int (*) (struct clk_branch const*,int)) ; 
 int /*<<< orphan*/  clk_disable_regmap (struct clk_hw*) ; 
 int clk_enable_regmap (struct clk_hw*) ; 
 struct clk_branch* to_clk_branch (struct clk_hw*) ; 

__attribute__((used)) static int clk_branch_toggle(struct clk_hw *hw, bool en,
		bool (check_halt)(const struct clk_branch *, bool))
{
	struct clk_branch *br = to_clk_branch(hw);
	int ret;

	if (en) {
		ret = clk_enable_regmap(hw);
		if (ret)
			return ret;
	} else {
		clk_disable_regmap(hw);
	}

	return clk_branch_wait(br, en, check_halt);
}