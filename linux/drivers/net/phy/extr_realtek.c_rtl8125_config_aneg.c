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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_2500baseT_Full_BIT ; 
 int /*<<< orphan*/  RTL_ADV_2500FULL ; 
 int __genphy_config_aneg (struct phy_device*,int) ; 
 scalar_t__ linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_modify_paged_changed (struct phy_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8125_config_aneg(struct phy_device *phydev)
{
	int ret = 0;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		u16 adv2500 = 0;

		if (linkmode_test_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				      phydev->advertising))
			adv2500 = RTL_ADV_2500FULL;

		ret = phy_modify_paged_changed(phydev, 0xa5d, 0x12,
					       RTL_ADV_2500FULL, adv2500);
		if (ret < 0)
			return ret;
	}

	return __genphy_config_aneg(phydev, ret);
}