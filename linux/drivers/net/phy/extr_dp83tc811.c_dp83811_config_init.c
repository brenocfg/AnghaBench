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
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP83811_DEVADDR ; 
 int DP83811_SGMII_EN ; 
 int DP83811_WOL_EN ; 
 int DP83811_WOL_MAGIC_EN ; 
 int DP83811_WOL_SECURE_ON ; 
 int /*<<< orphan*/  MII_DP83811_SGMII_CTRL ; 
 int /*<<< orphan*/  MII_DP83811_WOL_CFG ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dp83811_config_init(struct phy_device *phydev)
{
	int value, err;

	value = phy_read(phydev, MII_DP83811_SGMII_CTRL);
	if (phydev->interface == PHY_INTERFACE_MODE_SGMII) {
		err = phy_write(phydev, MII_DP83811_SGMII_CTRL,
					(DP83811_SGMII_EN | value));
	} else {
		err = phy_write(phydev, MII_DP83811_SGMII_CTRL,
				(~DP83811_SGMII_EN & value));
	}

	if (err < 0)

		return err;

	value = DP83811_WOL_MAGIC_EN | DP83811_WOL_SECURE_ON | DP83811_WOL_EN;

	return phy_write_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_CFG,
	      value);
}