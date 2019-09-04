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
struct device_driver {int /*<<< orphan*/  bus; } ;
struct device {struct device* parent; int /*<<< orphan*/ * driver; } ;
struct bus_type {scalar_t__ need_parent_lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 struct device* bus_find_device_by_name (struct bus_type*,int /*<<< orphan*/ *,char const*) ; 
 struct bus_type* bus_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_put (struct bus_type*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 scalar_t__ driver_match_device (struct device_driver*,struct device*) ; 
 int driver_probe_device (struct device_driver*,struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static ssize_t bind_store(struct device_driver *drv, const char *buf,
			  size_t count)
{
	struct bus_type *bus = bus_get(drv->bus);
	struct device *dev;
	int err = -ENODEV;

	dev = bus_find_device_by_name(bus, NULL, buf);
	if (dev && dev->driver == NULL && driver_match_device(drv, dev)) {
		if (dev->parent && bus->need_parent_lock)
			device_lock(dev->parent);
		device_lock(dev);
		err = driver_probe_device(drv, dev);
		device_unlock(dev);
		if (dev->parent && bus->need_parent_lock)
			device_unlock(dev->parent);

		if (err > 0) {
			/* success */
			err = count;
		} else if (err == 0) {
			/* driver didn't accept device */
			err = -ENODEV;
		}
	}
	put_device(dev);
	bus_put(bus);
	return err;
}