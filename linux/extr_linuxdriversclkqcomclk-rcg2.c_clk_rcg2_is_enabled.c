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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg2 {scalar_t__ cmd_rcgr; TYPE_1__ clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMD_REG ; 
 int CMD_ROOT_OFF ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg2_is_enabled(struct clk_hw *hw)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 cmd;
	int ret;

	ret = regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG, &cmd);
	if (ret)
		return ret;

	return (cmd & CMD_ROOT_OFF) == 0;
}