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
typedef  int u16 ;
struct e1000_phy_info {int min_cable_length; int max_cable_length; int cable_length; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_PHY ; 
 int GG82563_CABLE_LENGTH_TABLE_SIZE ; 
 int GG82563_DSPD_CABLE_LENGTH ; 
 int /*<<< orphan*/  GG82563_PHY_DSP_DISTANCE ; 
 void** e1000_gg82563_cable_length_table ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static s32 e1000_get_cable_length_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, index;

	ret_val = e1e_rphy(hw, GG82563_PHY_DSP_DISTANCE, &phy_data);
	if (ret_val)
		return ret_val;

	index = phy_data & GG82563_DSPD_CABLE_LENGTH;

	if (index >= GG82563_CABLE_LENGTH_TABLE_SIZE - 5)
		return -E1000_ERR_PHY;

	phy->min_cable_length = e1000_gg82563_cable_length_table[index];
	phy->max_cable_length = e1000_gg82563_cable_length_table[index + 5];

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

	return 0;
}