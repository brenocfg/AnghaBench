#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; } ;

/* Variables and functions */
 int device_add (int /*<<< orphan*/ *) ; 
 int mdiobus_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_device_reset (struct phy_device*,int) ; 
 int phy_scan_fixups (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 

int phy_device_register(struct phy_device *phydev)
{
	int err;

	err = mdiobus_register_device(&phydev->mdio);
	if (err)
		return err;

	/* Deassert the reset signal */
	phy_device_reset(phydev, 0);

	/* Run all of the fixups for this PHY */
	err = phy_scan_fixups(phydev);
	if (err) {
		phydev_err(phydev, "failed to initialize\n");
		goto out;
	}

	err = device_add(&phydev->mdio.dev);
	if (err) {
		phydev_err(phydev, "failed to add\n");
		goto out;
	}

	return 0;

 out:
	/* Assert the reset signal */
	phy_device_reset(phydev, 1);

	mdiobus_unregister_device(&phydev->mdio);
	return err;
}