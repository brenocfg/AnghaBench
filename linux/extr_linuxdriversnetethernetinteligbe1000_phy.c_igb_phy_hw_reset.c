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
struct TYPE_2__ {scalar_t__ (* get_cfg_done ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {int reset_delay_us; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_PHY_RST ; 
 scalar_t__ igb_check_reset_block (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 scalar_t__ stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

s32 igb_phy_hw_reset(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32  ret_val;
	u32 ctrl;

	ret_val = igb_check_reset_block(hw);
	if (ret_val) {
		ret_val = 0;
		goto out;
	}

	ret_val = phy->ops.acquire(hw);
	if (ret_val)
		goto out;

	ctrl = rd32(E1000_CTRL);
	wr32(E1000_CTRL, ctrl | E1000_CTRL_PHY_RST);
	wrfl();

	udelay(phy->reset_delay_us);

	wr32(E1000_CTRL, ctrl);
	wrfl();

	udelay(150);

	phy->ops.release(hw);

	ret_val = phy->ops.get_cfg_done(hw);

out:
	return ret_val;
}