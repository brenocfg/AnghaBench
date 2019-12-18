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
struct module {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bus; struct module* owner; } ;
struct i3c_driver {TYPE_1__ driver; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i3c_bus_type ; 

int i3c_driver_register_with_owner(struct i3c_driver *drv, struct module *owner)
{
	drv->driver.owner = owner;
	drv->driver.bus = &i3c_bus_type;

	return driver_register(&drv->driver);
}