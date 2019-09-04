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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct root_device {TYPE_1__ dev; scalar_t__ owner; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 struct root_device* to_root_device (struct device*) ; 

void root_device_unregister(struct device *dev)
{
	struct root_device *root = to_root_device(dev);

	if (root->owner)
		sysfs_remove_link(&root->dev.kobj, "module");

	device_unregister(dev);
}