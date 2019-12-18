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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; struct module* owner; int /*<<< orphan*/ * bus; } ;
struct sdw_driver {TYPE_1__ driver; scalar_t__ shutdown; scalar_t__ remove; int /*<<< orphan*/  name; int /*<<< orphan*/  probe; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdw_bus_type ; 
 int /*<<< orphan*/  sdw_drv_probe ; 
 int /*<<< orphan*/  sdw_drv_remove ; 
 int /*<<< orphan*/  sdw_drv_shutdown ; 

int __sdw_register_driver(struct sdw_driver *drv, struct module *owner)
{
	drv->driver.bus = &sdw_bus_type;

	if (!drv->probe) {
		pr_err("driver %s didn't provide SDW probe routine\n",
		       drv->name);
		return -EINVAL;
	}

	drv->driver.owner = owner;
	drv->driver.probe = sdw_drv_probe;

	if (drv->remove)
		drv->driver.remove = sdw_drv_remove;

	if (drv->shutdown)
		drv->driver.shutdown = sdw_drv_shutdown;

	return driver_register(&drv->driver);
}