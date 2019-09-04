#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device_driver {int /*<<< orphan*/  groups; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  bus_remove_driver (struct device_driver*) ; 
 int /*<<< orphan*/  driver_remove_groups (struct device_driver*,int /*<<< orphan*/ ) ; 

void driver_unregister(struct device_driver *drv)
{
	if (!drv || !drv->p) {
		WARN(1, "Unexpected driver unregister!\n");
		return;
	}
	driver_remove_groups(drv, drv->groups);
	bus_remove_driver(drv);
}