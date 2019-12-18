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
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct visor_driver {TYPE_1__ driver; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; int /*<<< orphan*/  resume; int /*<<< orphan*/  pause; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  visorbus_type ; 
 int /*<<< orphan*/  visordriver_probe_device ; 
 int /*<<< orphan*/  visordriver_remove_device ; 

int visorbus_register_visor_driver(struct visor_driver *drv)
{
	/* can't register on a nonexistent bus */
	if (!initialized)
		return -ENODEV;
	if (!drv->probe)
		return -EINVAL;
	if (!drv->remove)
		return -EINVAL;
	if (!drv->pause)
		return -EINVAL;
	if (!drv->resume)
		return -EINVAL;

	drv->driver.name = drv->name;
	drv->driver.bus = &visorbus_type;
	drv->driver.probe = visordriver_probe_device;
	drv->driver.remove = visordriver_remove_device;
	drv->driver.owner = drv->owner;
	/*
	 * driver_register does this:
	 *   bus_add_driver(drv)
	 *   ->if (drv.bus)  ** (bus_type) **
	 *       driver_attach(drv)
	 *         for each dev with bus type of drv.bus
	 *           if (!dev.drv)  ** no driver assigned yet **
	 *             if (bus.match(dev,drv))  [visorbus_match]
	 *               dev.drv = drv
	 *               if (!drv.probe(dev))   [visordriver_probe_device]
	 *                 dev.drv = NULL
	 */
	return driver_register(&drv->driver);
}