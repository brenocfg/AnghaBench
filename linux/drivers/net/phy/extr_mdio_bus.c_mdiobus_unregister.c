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
struct mii_bus {scalar_t__ state; int /*<<< orphan*/  dev; scalar_t__ reset_gpiod; struct mdio_device** mdio_map; } ;
struct mdio_device {int /*<<< orphan*/  (* device_free ) (struct mdio_device*) ;int /*<<< orphan*/  (* device_remove ) (struct mdio_device*) ;scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MDIOBUS_REGISTERED ; 
 scalar_t__ MDIOBUS_UNREGISTERED ; 
 int PHY_MAX_ADDR ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct mdio_device*) ; 
 int /*<<< orphan*/  stub2 (struct mdio_device*) ; 

void mdiobus_unregister(struct mii_bus *bus)
{
	struct mdio_device *mdiodev;
	int i;

	BUG_ON(bus->state != MDIOBUS_REGISTERED);
	bus->state = MDIOBUS_UNREGISTERED;

	for (i = 0; i < PHY_MAX_ADDR; i++) {
		mdiodev = bus->mdio_map[i];
		if (!mdiodev)
			continue;

		if (mdiodev->reset_gpio)
			gpiod_put(mdiodev->reset_gpio);

		mdiodev->device_remove(mdiodev);
		mdiodev->device_free(mdiodev);
	}

	/* Put PHYs in RESET to save power */
	if (bus->reset_gpiod)
		gpiod_set_value_cansleep(bus->reset_gpiod, 1);

	device_del(&bus->dev);
}