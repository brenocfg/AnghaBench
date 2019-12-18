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
struct mdio_driver {int /*<<< orphan*/  (* remove ) (struct mdio_device*) ;} ;
struct TYPE_2__ {struct device_driver* driver; } ;
struct mdio_device {TYPE_1__ dev; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdio_device_reset (struct mdio_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct mdio_device*) ; 
 struct mdio_device* to_mdio_device (struct device*) ; 
 struct mdio_driver* to_mdio_driver (struct device_driver*) ; 

__attribute__((used)) static int mdio_remove(struct device *dev)
{
	struct mdio_device *mdiodev = to_mdio_device(dev);
	struct device_driver *drv = mdiodev->dev.driver;
	struct mdio_driver *mdiodrv = to_mdio_driver(drv);

	if (mdiodrv->remove) {
		mdiodrv->remove(mdiodev);

		/* Assert the reset signal */
		mdio_device_reset(mdiodev, 1);
	}

	return 0;
}