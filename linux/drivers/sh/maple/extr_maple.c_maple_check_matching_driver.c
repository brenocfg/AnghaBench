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
struct maple_driver {int /*<<< orphan*/  function; } ;
struct TYPE_2__ {int function; } ;
struct maple_device {TYPE_1__ devinfo; } ;
struct device_driver {int dummy; } ;

/* Variables and functions */
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct maple_driver* to_maple_driver (struct device_driver*) ; 

__attribute__((used)) static int maple_check_matching_driver(struct device_driver *driver,
					void *devptr)
{
	struct maple_driver *maple_drv;
	struct maple_device *mdev;

	mdev = devptr;
	maple_drv = to_maple_driver(driver);
	if (mdev->devinfo.function & cpu_to_be32(maple_drv->function))
		return 1;
	return 0;
}