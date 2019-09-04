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
struct TYPE_2__ {char const* mod_name; struct module* owner; int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct vio_driver {TYPE_1__ driver; int /*<<< orphan*/  name; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  vio_bus_type ; 

int __vio_register_driver(struct vio_driver *viodrv, struct module *owner,
			const char *mod_name)
{
	viodrv->driver.bus = &vio_bus_type;
	viodrv->driver.name = viodrv->name;
	viodrv->driver.owner = owner;
	viodrv->driver.mod_name = mod_name;

	return driver_register(&viodrv->driver);
}