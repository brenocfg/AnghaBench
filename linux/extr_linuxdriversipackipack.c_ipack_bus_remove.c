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
struct ipack_driver {TYPE_1__* ops; } ;
struct ipack_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct ipack_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (struct ipack_device*) ; 
 struct ipack_device* to_ipack_dev (struct device*) ; 
 struct ipack_driver* to_ipack_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipack_bus_remove(struct device *device)
{
	struct ipack_device *dev = to_ipack_dev(device);
	struct ipack_driver *drv = to_ipack_driver(device->driver);

	if (!drv->ops->remove)
		return -EINVAL;

	drv->ops->remove(dev);
	return 0;
}