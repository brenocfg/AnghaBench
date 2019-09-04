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
struct device_driver {int /*<<< orphan*/  bus; } ;
struct device {scalar_t__ parent; TYPE_1__* bus; struct device_driver* driver; } ;
struct bus_type {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ need_parent_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 struct device* bus_find_device_by_name (struct bus_type*,int /*<<< orphan*/ *,char const*) ; 
 struct bus_type* bus_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_put (struct bus_type*) ; 
 int /*<<< orphan*/  device_lock (scalar_t__) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  device_unlock (scalar_t__) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static ssize_t unbind_store(struct device_driver *drv, const char *buf,
			    size_t count)
{
	struct bus_type *bus = bus_get(drv->bus);
	struct device *dev;
	int err = -ENODEV;

	dev = bus_find_device_by_name(bus, NULL, buf);
	if (dev && dev->driver == drv) {
		if (dev->parent && dev->bus->need_parent_lock)
			device_lock(dev->parent);
		device_release_driver(dev);
		if (dev->parent && dev->bus->need_parent_lock)
			device_unlock(dev->parent);
		err = count;
	}
	put_device(dev);
	bus_put(bus);
	return err;
}