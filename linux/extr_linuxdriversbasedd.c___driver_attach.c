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
struct device_driver {int dummy; } ;
struct device {struct device* parent; TYPE_1__* bus; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {scalar_t__ need_parent_lock; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  driver_deferred_probe_add (struct device*) ; 
 int driver_match_device (struct device_driver*,struct device*) ; 
 int /*<<< orphan*/  driver_probe_device (struct device_driver*,struct device*) ; 

__attribute__((used)) static int __driver_attach(struct device *dev, void *data)
{
	struct device_driver *drv = data;
	int ret;

	/*
	 * Lock device and try to bind to it. We drop the error
	 * here and always return 0, because we need to keep trying
	 * to bind to devices and some drivers will return an error
	 * simply if it didn't support the device.
	 *
	 * driver_probe_device() will spit a warning if there
	 * is an error.
	 */

	ret = driver_match_device(drv, dev);
	if (ret == 0) {
		/* no match */
		return 0;
	} else if (ret == -EPROBE_DEFER) {
		dev_dbg(dev, "Device match requests probe deferral\n");
		driver_deferred_probe_add(dev);
	} else if (ret < 0) {
		dev_dbg(dev, "Bus failed to match device: %d", ret);
		return ret;
	} /* ret > 0 means positive match */

	if (dev->parent && dev->bus->need_parent_lock)
		device_lock(dev->parent);
	device_lock(dev);
	if (!dev->driver)
		driver_probe_device(drv, dev);
	device_unlock(dev);
	if (dev->parent && dev->bus->need_parent_lock)
		device_unlock(dev->parent);

	return 0;
}