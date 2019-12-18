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
struct device {int dummy; } ;
struct ccwgroup_driver {int /*<<< orphan*/  driver; } ;
struct ccwgroup_device {int dummy; } ;

/* Variables and functions */
 struct device* driver_find_device_by_name (int /*<<< orphan*/ *,char*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

struct ccwgroup_device *get_ccwgroupdev_by_busid(struct ccwgroup_driver *gdrv,
						 char *bus_id)
{
	struct device *dev;

	dev = driver_find_device_by_name(&gdrv->driver, bus_id);

	return dev ? to_ccwgroupdev(dev) : NULL;
}