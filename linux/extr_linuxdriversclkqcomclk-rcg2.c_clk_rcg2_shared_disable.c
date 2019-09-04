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
struct clk_rcg2 {int safe_src_index; scalar_t__ cmd_rcgr; TYPE_1__ clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFG_REG ; 
 int CFG_SRC_SEL_SHIFT ; 
 int /*<<< orphan*/  clk_rcg2_clear_force_enable (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_rcg2_set_force_enable (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 
 int /*<<< orphan*/  update_config (struct clk_rcg2*) ; 

__attribute__((used)) static void clk_rcg2_shared_disable(struct clk_hw *hw)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 cfg;

	/*
	 * Store current configuration as switching to safe source would clear
	 * the SRC and DIV of CFG register
	 */
	regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);

	/*
	 * Park the RCG at a safe configuration - sourced off of safe source.
	 * Force enable and disable the RCG while configuring it to safeguard
	 * against any update signal coming from the downstream clock.
	 * The current parent is still prepared and enabled at this point, and
	 * the safe source is always on while application processor subsystem
	 * is online. Therefore, the RCG can safely switch its parent.
	 */
	clk_rcg2_set_force_enable(hw);

	regmap_write(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
		     rcg->safe_src_index << CFG_SRC_SEL_SHIFT);

	update_config(rcg);

	clk_rcg2_clear_force_enable(hw);

	/* Write back the stored configuration corresponding to current rate */
	regmap_write(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, cfg);
}