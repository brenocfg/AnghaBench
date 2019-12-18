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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {scalar_t__ phy_id; int phy_revision; int mac_type; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_CONFIG ; 
 scalar_t__ E1000_ERR_PHY ; 
 scalar_t__ E1000_SUCCESS ; 
 int IGP01E1000_I_PHY_ID ; 
 int M88E1000_E_PHY_ID ; 
 int M88E1000_I_PHY_ID ; 
 int M88E1011_I_PHY_ID ; 
 int M88E1118_E_PHY_ID ; 
 int /*<<< orphan*/  PHY_ID1 ; 
 int /*<<< orphan*/  PHY_ID2 ; 
 int PHY_REVISION_MASK ; 
 int RTL8201N_PHY_ID ; 
 int RTL8211B_PHY_ID ; 
#define  e1000_82540 139 
#define  e1000_82541 138 
#define  e1000_82541_rev_2 137 
#define  e1000_82543 136 
#define  e1000_82544 135 
#define  e1000_82545 134 
#define  e1000_82545_rev_3 133 
#define  e1000_82546 132 
#define  e1000_82546_rev_3 131 
#define  e1000_82547 130 
#define  e1000_82547_rev_2 129 
#define  e1000_ce4100 128 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_set_phy_type (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_detect_gig_phy(struct e1000_hw *hw)
{
	s32 phy_init_status, ret_val;
	u16 phy_id_high, phy_id_low;
	bool match = false;

	if (hw->phy_id != 0)
		return E1000_SUCCESS;

	/* Read the PHY ID Registers to identify which PHY is onboard. */
	ret_val = e1000_read_phy_reg(hw, PHY_ID1, &phy_id_high);
	if (ret_val)
		return ret_val;

	hw->phy_id = (u32)(phy_id_high << 16);
	udelay(20);
	ret_val = e1000_read_phy_reg(hw, PHY_ID2, &phy_id_low);
	if (ret_val)
		return ret_val;

	hw->phy_id |= (u32)(phy_id_low & PHY_REVISION_MASK);
	hw->phy_revision = (u32)phy_id_low & ~PHY_REVISION_MASK;

	switch (hw->mac_type) {
	case e1000_82543:
		if (hw->phy_id == M88E1000_E_PHY_ID)
			match = true;
		break;
	case e1000_82544:
		if (hw->phy_id == M88E1000_I_PHY_ID)
			match = true;
		break;
	case e1000_82540:
	case e1000_82545:
	case e1000_82545_rev_3:
	case e1000_82546:
	case e1000_82546_rev_3:
		if (hw->phy_id == M88E1011_I_PHY_ID)
			match = true;
		break;
	case e1000_ce4100:
		if ((hw->phy_id == RTL8211B_PHY_ID) ||
		    (hw->phy_id == RTL8201N_PHY_ID) ||
		    (hw->phy_id == M88E1118_E_PHY_ID))
			match = true;
		break;
	case e1000_82541:
	case e1000_82541_rev_2:
	case e1000_82547:
	case e1000_82547_rev_2:
		if (hw->phy_id == IGP01E1000_I_PHY_ID)
			match = true;
		break;
	default:
		e_dbg("Invalid MAC type %d\n", hw->mac_type);
		return -E1000_ERR_CONFIG;
	}
	phy_init_status = e1000_set_phy_type(hw);

	if ((match) && (phy_init_status == E1000_SUCCESS)) {
		e_dbg("PHY ID 0x%X detected\n", hw->phy_id);
		return E1000_SUCCESS;
	}
	e_dbg("Invalid PHY ID 0x%X\n", hw->phy_id);
	return -E1000_ERR_PHY;
}