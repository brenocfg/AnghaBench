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
struct TYPE_2__ {int flags; } ;
struct mdio_driver {TYPE_1__ mdiodrv; } ;
struct mdio_device {int /*<<< orphan*/  modalias; } ;
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int MDIO_DEVICE_IS_PHY ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdio_device* to_mdio_device (struct device*) ; 
 struct mdio_driver* to_mdio_driver (struct device_driver*) ; 

int mdio_device_bus_match(struct device *dev, struct device_driver *drv)
{
	struct mdio_device *mdiodev = to_mdio_device(dev);
	struct mdio_driver *mdiodrv = to_mdio_driver(drv);

	if (mdiodrv->mdiodrv.flags & MDIO_DEVICE_IS_PHY)
		return 0;

	return strcmp(mdiodev->modalias, drv->name) == 0;
}