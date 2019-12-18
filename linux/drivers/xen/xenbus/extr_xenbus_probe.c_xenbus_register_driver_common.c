#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* mod_name; struct module* owner; int /*<<< orphan*/ * bus; scalar_t__ name; } ;
struct xenbus_driver {TYPE_2__ driver; TYPE_1__* ids; scalar_t__ name; } ;
struct xen_bus_type {int /*<<< orphan*/  bus; } ;
struct module {int dummy; } ;
struct TYPE_3__ {scalar_t__ devicetype; } ;

/* Variables and functions */
 int driver_register (TYPE_2__*) ; 

int xenbus_register_driver_common(struct xenbus_driver *drv,
				  struct xen_bus_type *bus,
				  struct module *owner, const char *mod_name)
{
	drv->driver.name = drv->name ? drv->name : drv->ids[0].devicetype;
	drv->driver.bus = &bus->bus;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	return driver_register(&drv->driver);
}