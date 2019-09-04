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
struct device {scalar_t__ parent; TYPE_1__* bus; scalar_t__ driver; } ;
struct TYPE_2__ {scalar_t__ need_parent_lock; } ;

/* Variables and functions */
 int bus_rescan_devices_helper (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (scalar_t__) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  device_unlock (scalar_t__) ; 

int device_reprobe(struct device *dev)
{
	if (dev->driver) {
		if (dev->parent && dev->bus->need_parent_lock)
			device_lock(dev->parent);
		device_release_driver(dev);
		if (dev->parent && dev->bus->need_parent_lock)
			device_unlock(dev->parent);
	}
	return bus_rescan_devices_helper(dev, NULL);
}