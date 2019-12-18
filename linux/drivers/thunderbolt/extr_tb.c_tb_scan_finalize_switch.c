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
struct tb_switch {int authorized; scalar_t__ boot; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (struct device*,int) ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int (*) (struct device*,void*)) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tb_is_switch (struct device*) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static int tb_scan_finalize_switch(struct device *dev, void *data)
{
	if (tb_is_switch(dev)) {
		struct tb_switch *sw = tb_to_switch(dev);

		/*
		 * If we found that the switch was already setup by the
		 * boot firmware, mark it as authorized now before we
		 * send uevent to userspace.
		 */
		if (sw->boot)
			sw->authorized = 1;

		dev_set_uevent_suppress(dev, false);
		kobject_uevent(&dev->kobj, KOBJ_ADD);
		device_for_each_child(dev, NULL, tb_scan_finalize_switch);
	}

	return 0;
}