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
struct rio_driver {int /*<<< orphan*/  (* remove ) (struct rio_dev*) ;} ;
struct rio_dev {struct rio_driver* driver; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rio_dev_put (struct rio_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rio_dev*) ; 
 struct rio_dev* to_rio_dev (struct device*) ; 

__attribute__((used)) static int rio_device_remove(struct device *dev)
{
	struct rio_dev *rdev = to_rio_dev(dev);
	struct rio_driver *rdrv = rdev->driver;

	if (rdrv) {
		if (rdrv->remove)
			rdrv->remove(rdev);
		rdev->driver = NULL;
	}

	rio_dev_put(rdev);

	return 0;
}