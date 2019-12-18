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
 int /*<<< orphan*/  ccwgroup_ungroup (struct ccwgroup_device*) ; 
 struct device* driver_find_next_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

void ccwgroup_driver_unregister(struct ccwgroup_driver *cdriver)
{
	struct device *dev;

	/* We don't want ccwgroup devices to live longer than their driver. */
	while ((dev = driver_find_next_device(&cdriver->driver, NULL))) {
		struct ccwgroup_device *gdev = to_ccwgroupdev(dev);

		ccwgroup_ungroup(gdev);
		put_device(dev);
	}
	driver_unregister(&cdriver->driver);
}