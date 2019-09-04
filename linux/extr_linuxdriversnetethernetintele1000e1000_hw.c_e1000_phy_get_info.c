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
struct e1000_phy_info {void* remote_rx; void* local_rx; int /*<<< orphan*/  mdix_mode; int /*<<< orphan*/  polarity_correction; int /*<<< orphan*/  downshift; int /*<<< orphan*/  cable_polarity; int /*<<< orphan*/  extended_10bt_distance; int /*<<< orphan*/  cable_length; } ;
struct e1000_hw {scalar_t__ media_type; scalar_t__ phy_type; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_CONFIG ; 
 scalar_t__ E1000_SUCCESS ; 
 int MII_SR_LINK_STATUS ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 void* e1000_1000t_rx_status_undefined ; 
 int /*<<< orphan*/  e1000_10bt_ext_dist_enable_undefined ; 
 int /*<<< orphan*/  e1000_auto_x_mode_undefined ; 
 int /*<<< orphan*/  e1000_cable_length_undefined ; 
 int /*<<< orphan*/  e1000_downshift_undefined ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_phy_8201 ; 
 scalar_t__ e1000_phy_8211 ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_phy_igp_get_info (struct e1000_hw*,struct e1000_phy_info*) ; 
 scalar_t__ e1000_phy_m88_get_info (struct e1000_hw*,struct e1000_phy_info*) ; 
 int /*<<< orphan*/  e1000_polarity_reversal_undefined ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_rev_polarity_undefined ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

s32 e1000_phy_get_info(struct e1000_hw *hw, struct e1000_phy_info *phy_info)
{
	s32 ret_val;
	u16 phy_data;

	phy_info->cable_length = e1000_cable_length_undefined;
	phy_info->extended_10bt_distance = e1000_10bt_ext_dist_enable_undefined;
	phy_info->cable_polarity = e1000_rev_polarity_undefined;
	phy_info->downshift = e1000_downshift_undefined;
	phy_info->polarity_correction = e1000_polarity_reversal_undefined;
	phy_info->mdix_mode = e1000_auto_x_mode_undefined;
	phy_info->local_rx = e1000_1000t_rx_status_undefined;
	phy_info->remote_rx = e1000_1000t_rx_status_undefined;

	if (hw->media_type != e1000_media_type_copper) {
		e_dbg("PHY info is only valid for copper media\n");
		return -E1000_ERR_CONFIG;
	}

	ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
	if (ret_val)
		return ret_val;

	ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
	if (ret_val)
		return ret_val;

	if ((phy_data & MII_SR_LINK_STATUS) != MII_SR_LINK_STATUS) {
		e_dbg("PHY info is only valid if link is up\n");
		return -E1000_ERR_CONFIG;
	}

	if (hw->phy_type == e1000_phy_igp)
		return e1000_phy_igp_get_info(hw, phy_info);
	else if ((hw->phy_type == e1000_phy_8211) ||
		 (hw->phy_type == e1000_phy_8201))
		return E1000_SUCCESS;
	else
		return e1000_phy_m88_get_info(hw, phy_info);
}