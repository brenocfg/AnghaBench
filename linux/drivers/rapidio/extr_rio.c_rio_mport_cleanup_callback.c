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
struct rio_dev {int dummy; } ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DEVICE_SHUTDOWN ; 
 int /*<<< orphan*/  rio_bus_type ; 
 int /*<<< orphan*/  rio_del_device (struct rio_dev*,int /*<<< orphan*/ ) ; 
 struct rio_dev* to_rio_dev (struct device*) ; 

__attribute__((used)) static int rio_mport_cleanup_callback(struct device *dev, void *data)
{
	struct rio_dev *rdev = to_rio_dev(dev);

	if (dev->bus == &rio_bus_type)
		rio_del_device(rdev, RIO_DEVICE_SHUTDOWN);
	return 0;
}