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
struct mdio_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int mdiobus_register_device (struct mdio_device*) ; 
 int /*<<< orphan*/  mdiobus_unregister_device (struct mdio_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int mdio_device_register(struct mdio_device *mdiodev)
{
	int err;

	dev_dbg(&mdiodev->dev, "mdio_device_register\n");

	err = mdiobus_register_device(mdiodev);
	if (err)
		return err;

	err = device_add(&mdiodev->dev);
	if (err) {
		pr_err("MDIO %d failed to add\n", mdiodev->addr);
		goto out;
	}

	return 0;

 out:
	mdiobus_unregister_device(mdiodev);
	return err;
}