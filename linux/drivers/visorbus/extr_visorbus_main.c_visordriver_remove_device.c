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
struct visor_driver {int /*<<< orphan*/  (* remove ) (struct visor_device*) ;} ;
struct visor_device {int being_removed; int /*<<< orphan*/  device; int /*<<< orphan*/  visordriver_callback_lock; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_stop_periodic_work (struct visor_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct visor_device*) ; 
 struct visor_device* to_visor_device (struct device*) ; 
 struct visor_driver* to_visor_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visordriver_remove_device(struct device *xdev)
{
	struct visor_device *dev = to_visor_device(xdev);
	struct visor_driver *drv = to_visor_driver(xdev->driver);

	mutex_lock(&dev->visordriver_callback_lock);
	dev->being_removed = true;
	drv->remove(dev);
	mutex_unlock(&dev->visordriver_callback_lock);
	dev_stop_periodic_work(dev);
	put_device(&dev->device);
	return 0;
}