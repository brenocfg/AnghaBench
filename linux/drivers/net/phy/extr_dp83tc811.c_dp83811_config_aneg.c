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
struct phy_device {scalar_t__ interface; scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int DP83811_SGMII_AUTO_NEG_EN ; 
 int /*<<< orphan*/  MII_DP83811_SGMII_CTRL ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int genphy_config_aneg (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dp83811_config_aneg(struct phy_device *phydev)
{
	int value, err;

	if (phydev->interface == PHY_INTERFACE_MODE_SGMII) {
		value = phy_read(phydev, MII_DP83811_SGMII_CTRL);
		if (phydev->autoneg == AUTONEG_ENABLE) {
			err = phy_write(phydev, MII_DP83811_SGMII_CTRL,
					(DP83811_SGMII_AUTO_NEG_EN | value));
			if (err < 0)
				return err;
		} else {
			err = phy_write(phydev, MII_DP83811_SGMII_CTRL,
					(~DP83811_SGMII_AUTO_NEG_EN & value));
			if (err < 0)
				return err;
		}
	}

	return genphy_config_aneg(phydev);
}