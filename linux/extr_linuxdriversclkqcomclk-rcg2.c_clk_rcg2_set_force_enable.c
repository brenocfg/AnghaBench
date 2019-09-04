#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg2 {scalar_t__ cmd_rcgr; TYPE_1__ clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMD_REG ; 
 int /*<<< orphan*/  CMD_ROOT_EN ; 
 int ETIMEDOUT ; 
 char* clk_hw_get_name (struct clk_hw*) ; 
 scalar_t__ clk_rcg2_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int clk_rcg2_set_force_enable(struct clk_hw *hw)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	const char *name = clk_hw_get_name(hw);
	int ret, count;

	ret = regmap_update_bits(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG,
				 CMD_ROOT_EN, CMD_ROOT_EN);
	if (ret)
		return ret;

	/* wait for RCG to turn ON */
	for (count = 500; count > 0; count--) {
		if (clk_rcg2_is_enabled(hw))
			return 0;

		udelay(1);
	}

	pr_err("%s: RCG did not turn on\n", name);
	return -ETIMEDOUT;
}