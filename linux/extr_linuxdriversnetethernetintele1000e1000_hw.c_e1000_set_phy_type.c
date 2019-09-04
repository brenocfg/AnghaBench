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
struct e1000_hw {scalar_t__ mac_type; int phy_id; int /*<<< orphan*/  phy_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_PHY_TYPE ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
#define  IGP01E1000_I_PHY_ID 135 
#define  M88E1000_E_PHY_ID 134 
#define  M88E1000_I_PHY_ID 133 
#define  M88E1011_I_PHY_ID 132 
#define  M88E1111_I_PHY_ID 131 
#define  M88E1118_E_PHY_ID 130 
#define  RTL8201N_PHY_ID 129 
#define  RTL8211B_PHY_ID 128 
 scalar_t__ e1000_82541 ; 
 scalar_t__ e1000_82541_rev_2 ; 
 scalar_t__ e1000_82547 ; 
 scalar_t__ e1000_82547_rev_2 ; 
 int /*<<< orphan*/  e1000_phy_8201 ; 
 int /*<<< orphan*/  e1000_phy_8211 ; 
 int /*<<< orphan*/  e1000_phy_igp ; 
 int /*<<< orphan*/  e1000_phy_m88 ; 
 int /*<<< orphan*/  e1000_phy_undefined ; 
 scalar_t__ e1000_undefined ; 

__attribute__((used)) static s32 e1000_set_phy_type(struct e1000_hw *hw)
{
	if (hw->mac_type == e1000_undefined)
		return -E1000_ERR_PHY_TYPE;

	switch (hw->phy_id) {
	case M88E1000_E_PHY_ID:
	case M88E1000_I_PHY_ID:
	case M88E1011_I_PHY_ID:
	case M88E1111_I_PHY_ID:
	case M88E1118_E_PHY_ID:
		hw->phy_type = e1000_phy_m88;
		break;
	case IGP01E1000_I_PHY_ID:
		if (hw->mac_type == e1000_82541 ||
		    hw->mac_type == e1000_82541_rev_2 ||
		    hw->mac_type == e1000_82547 ||
		    hw->mac_type == e1000_82547_rev_2)
			hw->phy_type = e1000_phy_igp;
		break;
	case RTL8211B_PHY_ID:
		hw->phy_type = e1000_phy_8211;
		break;
	case RTL8201N_PHY_ID:
		hw->phy_type = e1000_phy_8201;
		break;
	default:
		/* Should never have loaded on this device */
		hw->phy_type = e1000_phy_undefined;
		return -E1000_ERR_PHY_TYPE;
	}

	return E1000_SUCCESS;
}