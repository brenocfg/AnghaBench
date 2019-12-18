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
struct serdev_device {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  serdev_device_remove (struct serdev_device*) ; 
 int /*<<< orphan*/  serdev_device_type ; 
 struct serdev_device* to_serdev_device (struct device*) ; 

__attribute__((used)) static int serdev_remove_device(struct device *dev, void *data)
{
	struct serdev_device *serdev = to_serdev_device(dev);
	if (dev->type == &serdev_device_type)
		serdev_device_remove(serdev);
	return 0;
}