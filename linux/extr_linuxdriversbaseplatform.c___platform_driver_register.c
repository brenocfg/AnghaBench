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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; struct module* owner; } ;
struct platform_driver {TYPE_1__ driver; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  platform_drv_probe ; 
 int /*<<< orphan*/  platform_drv_remove ; 
 int /*<<< orphan*/  platform_drv_shutdown ; 

int __platform_driver_register(struct platform_driver *drv,
				struct module *owner)
{
	drv->driver.owner = owner;
	drv->driver.bus = &platform_bus_type;
	drv->driver.probe = platform_drv_probe;
	drv->driver.remove = platform_drv_remove;
	drv->driver.shutdown = platform_drv_shutdown;

	return driver_register(&drv->driver);
}