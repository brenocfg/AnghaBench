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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int addr; struct mii_bus* bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIN1300_MII_EXT_REG_DATA ; 
 int /*<<< orphan*/  ADIN1300_MII_EXT_REG_PTR ; 
 int __mdiobus_read (struct mii_bus*,int,int /*<<< orphan*/ ) ; 
 int __mdiobus_write (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int adin_cl45_to_adin_reg (struct phy_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adin_read_mmd(struct phy_device *phydev, int devad, u16 regnum)
{
	struct mii_bus *bus = phydev->mdio.bus;
	int phy_addr = phydev->mdio.addr;
	int adin_regnum;
	int err;

	adin_regnum = adin_cl45_to_adin_reg(phydev, devad, regnum);
	if (adin_regnum < 0)
		return adin_regnum;

	err = __mdiobus_write(bus, phy_addr, ADIN1300_MII_EXT_REG_PTR,
			      adin_regnum);
	if (err)
		return err;

	return __mdiobus_read(bus, phy_addr, ADIN1300_MII_EXT_REG_DATA);
}