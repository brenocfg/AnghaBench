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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mei_device {int dev_state; TYPE_1__ cdev; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  enum mei_dev_state { ____Placeholder_mei_dev_state } mei_dev_state ;

/* Variables and functions */
 struct device* class_find_device_by_devt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_class ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void mei_set_devstate(struct mei_device *dev, enum mei_dev_state state)
{
	struct device *clsdev;

	if (dev->dev_state == state)
		return;

	dev->dev_state = state;

	clsdev = class_find_device_by_devt(mei_class, dev->cdev.dev);
	if (clsdev) {
		sysfs_notify(&clsdev->kobj, NULL, "dev_state");
		put_device(clsdev);
	}
}