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
struct module {int dummy; } ;
struct TYPE_4__ {char const* mod_name; int /*<<< orphan*/ * bus; struct module* owner; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct hv_driver {TYPE_2__ driver; TYPE_1__ dynids; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int driver_register (TYPE_2__*) ; 
 int /*<<< orphan*/  hv_bus ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vmbus_exists () ; 

int __vmbus_driver_register(struct hv_driver *hv_driver, struct module *owner, const char *mod_name)
{
	int ret;

	pr_info("registering driver %s\n", hv_driver->name);

	ret = vmbus_exists();
	if (ret < 0)
		return ret;

	hv_driver->driver.name = hv_driver->name;
	hv_driver->driver.owner = owner;
	hv_driver->driver.mod_name = mod_name;
	hv_driver->driver.bus = &hv_bus;

	spin_lock_init(&hv_driver->dynids.lock);
	INIT_LIST_HEAD(&hv_driver->dynids.list);

	ret = driver_register(&hv_driver->driver);

	return ret;
}