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
struct atl1c_hw {int autoneg_advertised; int link_cap_flags; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_DEFAULT_CAP ; 
 int ATL1C_LINK_CAP_1000M ; 
 int GIGA_CR_1000T_DEFAULT_CAP ; 
 int GIGA_CR_1000T_SPEED_MASK ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 scalar_t__ atl1c_write_phy_reg (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atl1c_phy_setup_adv(struct atl1c_hw *hw)
{
	u16 mii_adv_data = ADVERTISE_DEFAULT_CAP & ~ADVERTISE_ALL;
	u16 mii_giga_ctrl_data = GIGA_CR_1000T_DEFAULT_CAP &
				~GIGA_CR_1000T_SPEED_MASK;

	if (hw->autoneg_advertised & ADVERTISED_10baseT_Half)
		mii_adv_data |= ADVERTISE_10HALF;
	if (hw->autoneg_advertised & ADVERTISED_10baseT_Full)
		mii_adv_data |= ADVERTISE_10FULL;
	if (hw->autoneg_advertised & ADVERTISED_100baseT_Half)
		mii_adv_data |= ADVERTISE_100HALF;
	if (hw->autoneg_advertised & ADVERTISED_100baseT_Full)
		mii_adv_data |= ADVERTISE_100FULL;

	if (hw->autoneg_advertised & ADVERTISED_Autoneg)
		mii_adv_data |= ADVERTISE_10HALF  | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL;

	if (hw->link_cap_flags & ATL1C_LINK_CAP_1000M) {
		if (hw->autoneg_advertised & ADVERTISED_1000baseT_Half)
			mii_giga_ctrl_data |= ADVERTISE_1000HALF;
		if (hw->autoneg_advertised & ADVERTISED_1000baseT_Full)
			mii_giga_ctrl_data |= ADVERTISE_1000FULL;
		if (hw->autoneg_advertised & ADVERTISED_Autoneg)
			mii_giga_ctrl_data |= ADVERTISE_1000HALF |
					ADVERTISE_1000FULL;
	}

	if (atl1c_write_phy_reg(hw, MII_ADVERTISE, mii_adv_data) != 0 ||
	    atl1c_write_phy_reg(hw, MII_CTRL1000, mii_giga_ctrl_data) != 0)
		return -1;
	return 0;
}