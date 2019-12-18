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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; struct module* owner; } ;
struct mei_cl_driver {TYPE_1__ driver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mei_cl_bus_type ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int __mei_cldev_driver_register(struct mei_cl_driver *cldrv,
				struct module *owner)
{
	int err;

	cldrv->driver.name = cldrv->name;
	cldrv->driver.owner = owner;
	cldrv->driver.bus = &mei_cl_bus_type;

	err = driver_register(&cldrv->driver);
	if (err)
		return err;

	pr_debug("mei: driver [%s] registered\n", cldrv->driver.name);

	return 0;
}