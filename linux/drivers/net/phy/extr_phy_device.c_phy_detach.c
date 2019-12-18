#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* driver; int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {TYPE_6__ dev; struct mii_bus* bus; } ;
struct phy_device {TYPE_2__ mdio; int /*<<< orphan*/ * phylink; struct net_device* attached_dev; scalar_t__ sysfs_links; } ;
struct TYPE_13__ {TYPE_4__* parent; int /*<<< orphan*/  kobj; } ;
struct net_device {TYPE_5__ dev; int /*<<< orphan*/ * phydev; } ;
struct module {int dummy; } ;
struct mii_bus {struct module* owner; } ;
struct TYPE_15__ {int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {TYPE_3__* driver; } ;
struct TYPE_11__ {struct module* owner; } ;
struct TYPE_9__ {struct module* owner; } ;

/* Variables and functions */
 TYPE_8__ dev_attr_phy_standalone ; 
 int /*<<< orphan*/  device_release_driver (TYPE_6__*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  phy_device_reset (struct phy_device*,int) ; 
 scalar_t__ phy_driver_is_genphy (struct phy_device*) ; 
 scalar_t__ phy_driver_is_genphy_10g (struct phy_device*) ; 
 int /*<<< orphan*/  phy_led_triggers_unregister (struct phy_device*) ; 
 int /*<<< orphan*/  phy_suspend (struct phy_device*) ; 
 int /*<<< orphan*/  put_device (TYPE_6__*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void phy_detach(struct phy_device *phydev)
{
	struct net_device *dev = phydev->attached_dev;
	struct module *ndev_owner = NULL;
	struct mii_bus *bus;

	if (phydev->sysfs_links) {
		if (dev)
			sysfs_remove_link(&dev->dev.kobj, "phydev");
		sysfs_remove_link(&phydev->mdio.dev.kobj, "attached_dev");
	}

	if (!phydev->attached_dev)
		sysfs_remove_file(&phydev->mdio.dev.kobj,
				  &dev_attr_phy_standalone.attr);

	phy_suspend(phydev);
	if (dev) {
		phydev->attached_dev->phydev = NULL;
		phydev->attached_dev = NULL;
	}
	phydev->phylink = NULL;

	phy_led_triggers_unregister(phydev);

	module_put(phydev->mdio.dev.driver->owner);

	/* If the device had no specific driver before (i.e. - it
	 * was using the generic driver), we unbind the device
	 * from the generic driver so that there's a chance a
	 * real driver could be loaded
	 */
	if (phy_driver_is_genphy(phydev) ||
	    phy_driver_is_genphy_10g(phydev))
		device_release_driver(&phydev->mdio.dev);

	/*
	 * The phydev might go away on the put_device() below, so avoid
	 * a use-after-free bug by reading the underlying bus first.
	 */
	bus = phydev->mdio.bus;

	put_device(&phydev->mdio.dev);
	if (dev)
		ndev_owner = dev->dev.parent->driver->owner;
	if (ndev_owner != bus->owner)
		module_put(bus->owner);

	/* Assert the reset signal */
	phy_device_reset(phydev, 1);
}