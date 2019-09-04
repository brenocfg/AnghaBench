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
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  M88E1000_PHY_GEN_CONTROL ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_phy_reset_dsp(struct e1000_hw *hw)
{
	s32 ret_val = 0;

	if (!(hw->phy.ops.write_reg))
		goto out;

	ret_val = hw->phy.ops.write_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xC1);
	if (ret_val)
		goto out;

	ret_val = hw->phy.ops.write_reg(hw, M88E1000_PHY_GEN_CONTROL, 0);

out:
	return ret_val;
}