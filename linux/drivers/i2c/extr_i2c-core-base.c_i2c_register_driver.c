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
struct i2c_driver {TYPE_1__ driver; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __process_new_driver ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_bus_type ; 
 int /*<<< orphan*/  i2c_for_each_dev (struct i2c_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_registered ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int i2c_register_driver(struct module *owner, struct i2c_driver *driver)
{
	int res;

	/* Can't register until after driver model init */
	if (WARN_ON(!is_registered))
		return -EAGAIN;

	/* add the driver to the list of i2c drivers in the driver core */
	driver->driver.owner = owner;
	driver->driver.bus = &i2c_bus_type;
	INIT_LIST_HEAD(&driver->clients);

	/* When registration returns, the driver core
	 * will have called probe() for all matching-but-unbound devices.
	 */
	res = driver_register(&driver->driver);
	if (res)
		return res;

	pr_debug("driver [%s] registered\n", driver->driver.name);

	/* Walk the adapters that are already present */
	i2c_for_each_dev(driver, __process_new_driver);

	return 0;
}