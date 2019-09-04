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
typedef  int u16 ;
struct TYPE_2__ {int (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct e1000_phy_info {int cable_length; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int s32 ;

/* Variables and functions */
 int E1000_CABLE_LENGTH_UNDEFINED ; 
 int E1000_ERR_PHY ; 
 int I82580_DSTATUS_CABLE_LENGTH ; 
 int I82580_DSTATUS_CABLE_LENGTH_SHIFT ; 
 int /*<<< orphan*/  I82580_PHY_DIAG_STATUS ; 
 int stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 

s32 igb_get_cable_length_82580(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, length;

	ret_val = phy->ops.read_reg(hw, I82580_PHY_DIAG_STATUS, &phy_data);
	if (ret_val)
		goto out;

	length = (phy_data & I82580_DSTATUS_CABLE_LENGTH) >>
		 I82580_DSTATUS_CABLE_LENGTH_SHIFT;

	if (length == E1000_CABLE_LENGTH_UNDEFINED)
		ret_val = -E1000_ERR_PHY;

	phy->cable_length = length;

out:
	return ret_val;
}