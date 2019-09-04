#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_3__ {char const* mod_name; int /*<<< orphan*/  name; struct module* owner; int /*<<< orphan*/ * bus; } ;
struct gameport_driver {int ignore; TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMEPORT_ATTACH_DRIVER ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  gameport_bus ; 
 int gameport_queue_event (struct gameport_driver*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int __gameport_register_driver(struct gameport_driver *drv, struct module *owner,
				const char *mod_name)
{
	int error;

	drv->driver.bus = &gameport_bus;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	/*
	 * Temporarily disable automatic binding because probing
	 * takes long time and we are better off doing it in kgameportd
	 */
	drv->ignore = true;

	error = driver_register(&drv->driver);
	if (error) {
		pr_err("driver_register() failed for %s, error: %d\n",
			drv->driver.name, error);
		return error;
	}

	/*
	 * Reset ignore flag and let kgameportd bind the driver to free ports
	 */
	drv->ignore = false;
	error = gameport_queue_event(drv, NULL, GAMEPORT_ATTACH_DRIVER);
	if (error) {
		driver_unregister(&drv->driver);
		return error;
	}

	return 0;
}