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
struct TYPE_2__ {int can_wakeup; int /*<<< orphan*/  entry; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ device_is_registered (struct device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int wakeup_sysfs_add (struct device*) ; 
 int /*<<< orphan*/  wakeup_sysfs_remove (struct device*) ; 

void device_set_wakeup_capable(struct device *dev, bool capable)
{
	if (!!dev->power.can_wakeup == !!capable)
		return;

	dev->power.can_wakeup = capable;
	if (device_is_registered(dev) && !list_empty(&dev->power.entry)) {
		if (capable) {
			int ret = wakeup_sysfs_add(dev);

			if (ret)
				dev_info(dev, "Wakeup sysfs attributes not added\n");
		} else {
			wakeup_sysfs_remove(dev);
		}
	}
}