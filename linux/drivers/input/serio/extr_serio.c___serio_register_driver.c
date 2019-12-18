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
struct TYPE_3__ {char const* mod_name; int /*<<< orphan*/  name; struct module* owner; int /*<<< orphan*/ * bus; } ;
struct serio_driver {int manual_bind; TYPE_1__ driver; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERIO_ATTACH_DRIVER ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serio_bus ; 
 int serio_queue_event (struct serio_driver*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int __serio_register_driver(struct serio_driver *drv, struct module *owner, const char *mod_name)
{
	bool manual_bind = drv->manual_bind;
	int error;

	drv->driver.bus = &serio_bus;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	/*
	 * Temporarily disable automatic binding because probing
	 * takes long time and we are better off doing it in kseriod
	 */
	drv->manual_bind = true;

	error = driver_register(&drv->driver);
	if (error) {
		pr_err("driver_register() failed for %s, error: %d\n",
			drv->driver.name, error);
		return error;
	}

	/*
	 * Restore original bind mode and let kseriod bind the
	 * driver to free ports
	 */
	if (!manual_bind) {
		drv->manual_bind = false;
		error = serio_queue_event(drv, NULL, SERIO_ATTACH_DRIVER);
		if (error) {
			driver_unregister(&drv->driver);
			return error;
		}
	}

	return 0;
}