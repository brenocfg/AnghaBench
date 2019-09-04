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
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg2_clear_force_enable(struct clk_hw *hw)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);

	return regmap_update_bits(rcg->clkr.regmap, rcg->cmd_rcgr + CMD_REG,
					CMD_ROOT_EN, 0);
}