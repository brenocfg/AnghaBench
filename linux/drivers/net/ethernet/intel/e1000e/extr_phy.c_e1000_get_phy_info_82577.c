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
struct TYPE_2__ {scalar_t__ (* get_cable_length ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {int polarity_correction; int is_mdix; void* remote_rx; void* local_rx; int /*<<< orphan*/  cable_length; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CABLE_LENGTH_UNDEFINED ; 
 scalar_t__ E1000_ERR_CONFIG ; 
 int I82577_PHY_STATUS2_MDIX ; 
 int I82577_PHY_STATUS2_SPEED_1000MBPS ; 
 int I82577_PHY_STATUS2_SPEED_MASK ; 
 int /*<<< orphan*/  I82577_PHY_STATUS_2 ; 
 int LPA_1000LOCALRXOK ; 
 int LPA_1000REMRXOK ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 void* e1000_1000t_rx_status_not_ok ; 
 void* e1000_1000t_rx_status_ok ; 
 void* e1000_1000t_rx_status_undefined ; 
 scalar_t__ e1000_check_polarity_82577 (struct e1000_hw*) ; 
 scalar_t__ e1000e_phy_has_link_generic (struct e1000_hw*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 

s32 e1000_get_phy_info_82577(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	if (ret_val)
		return ret_val;

	if (!link) {
		e_dbg("Phy info is only valid if link is up\n");
		return -E1000_ERR_CONFIG;
	}

	phy->polarity_correction = true;

	ret_val = e1000_check_polarity_82577(hw);
	if (ret_val)
		return ret_val;

	ret_val = e1e_rphy(hw, I82577_PHY_STATUS_2, &data);
	if (ret_val)
		return ret_val;

	phy->is_mdix = !!(data & I82577_PHY_STATUS2_MDIX);

	if ((data & I82577_PHY_STATUS2_SPEED_MASK) ==
	    I82577_PHY_STATUS2_SPEED_1000MBPS) {
		ret_val = hw->phy.ops.get_cable_length(hw);
		if (ret_val)
			return ret_val;

		ret_val = e1e_rphy(hw, MII_STAT1000, &data);
		if (ret_val)
			return ret_val;

		phy->local_rx = (data & LPA_1000LOCALRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (data & LPA_1000REMRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
	} else {
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	}

	return 0;
}