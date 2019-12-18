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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  lp_advertising; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_2500baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_5000baseT_Full_BIT ; 
 int RTL_LPADV_10000FULL ; 
 int RTL_LPADV_2500FULL ; 
 int RTL_LPADV_5000FULL ; 
 int genphy_read_status (struct phy_device*) ; 
 int /*<<< orphan*/  linkmode_mod_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int phy_read_paged (struct phy_device*,int,int) ; 

__attribute__((used)) static int rtl8125_read_status(struct phy_device *phydev)
{
	if (phydev->autoneg == AUTONEG_ENABLE) {
		int lpadv = phy_read_paged(phydev, 0xa5d, 0x13);

		if (lpadv < 0)
			return lpadv;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
			phydev->lp_advertising, lpadv & RTL_LPADV_10000FULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
			phydev->lp_advertising, lpadv & RTL_LPADV_5000FULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			phydev->lp_advertising, lpadv & RTL_LPADV_2500FULL);
	}

	return genphy_read_status(phydev);
}