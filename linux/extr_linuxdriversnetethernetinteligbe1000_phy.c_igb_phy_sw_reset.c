#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CR_RESET ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 igb_phy_sw_reset(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u16 phy_ctrl;

	if (!(hw->phy.ops.read_reg))
		goto out;

	ret_val = hw->phy.ops.read_reg(hw, PHY_CONTROL, &phy_ctrl);
	if (ret_val)
		goto out;

	phy_ctrl |= MII_CR_RESET;
	ret_val = hw->phy.ops.write_reg(hw, PHY_CONTROL, phy_ctrl);
	if (ret_val)
		goto out;

	udelay(1);

out:
	return ret_val;
}