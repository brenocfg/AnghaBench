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
struct xenbus_driver {int /*<<< orphan*/  ids; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_xenbus_device (struct device*) ; 
 struct xenbus_driver* to_xenbus_driver (struct device_driver*) ; 

int xenbus_match(struct device *_dev, struct device_driver *_drv)
{
	struct xenbus_driver *drv = to_xenbus_driver(_drv);

	if (!drv->ids)
		return 0;

	return match_device(drv->ids, to_xenbus_device(_dev)) != NULL;
}