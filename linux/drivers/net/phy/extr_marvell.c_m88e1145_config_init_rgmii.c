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
struct phy_device {int dev_flags; } ;

/* Variables and functions */
 int MARVELL_PHY_M1145_FLAGS_RESISTANCE ; 
 int m88e1111_config_init_rgmii_delays (struct phy_device*) ; 
 int phy_modify (struct phy_device*,int,int,int) ; 
 int phy_write (struct phy_device*,int,int) ; 

__attribute__((used)) static int m88e1145_config_init_rgmii(struct phy_device *phydev)
{
	int err;

	err = m88e1111_config_init_rgmii_delays(phydev);
	if (err < 0)
		return err;

	if (phydev->dev_flags & MARVELL_PHY_M1145_FLAGS_RESISTANCE) {
		err = phy_write(phydev, 0x1d, 0x0012);
		if (err < 0)
			return err;

		err = phy_modify(phydev, 0x1e, 0x0fc0,
				 2 << 9 | /* 36 ohm */
				 2 << 6); /* 39 ohm */
		if (err < 0)
			return err;

		err = phy_write(phydev, 0x1d, 0x3);
		if (err < 0)
			return err;

		err = phy_write(phydev, 0x1e, 0x8000);
	}
	return err;
}