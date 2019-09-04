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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct i2c_driver {TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  __process_removed_driver ; 
 int /*<<< orphan*/  driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_for_each_dev (struct i2c_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void i2c_del_driver(struct i2c_driver *driver)
{
	i2c_for_each_dev(driver, __process_removed_driver);

	driver_unregister(&driver->driver);
	pr_debug("driver [%s] unregistered\n", driver->driver.name);
}