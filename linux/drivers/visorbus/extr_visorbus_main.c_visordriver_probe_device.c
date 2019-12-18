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
struct visor_driver {int (* probe ) (struct visor_device*) ;} ;
struct visor_device {int being_removed; int /*<<< orphan*/  visordriver_callback_lock; int /*<<< orphan*/  device; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  publish_vbus_dev_info (struct visor_device*) ; 
 int stub1 (struct visor_device*) ; 
 struct visor_device* to_visor_device (struct device*) ; 
 struct visor_driver* to_visor_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visordriver_probe_device(struct device *xdev)
{
	int err;
	struct visor_driver *drv = to_visor_driver(xdev->driver);
	struct visor_device *dev = to_visor_device(xdev);

	mutex_lock(&dev->visordriver_callback_lock);
	dev->being_removed = false;
	err = drv->probe(dev);
	if (err) {
		mutex_unlock(&dev->visordriver_callback_lock);
		return err;
	}
	/* success: reference kept via unmatched get_device() */
	get_device(&dev->device);
	publish_vbus_dev_info(dev);
	mutex_unlock(&dev->visordriver_callback_lock);
	return 0;
}