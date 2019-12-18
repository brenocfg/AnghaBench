#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct w1_slave {TYPE_2__ dev; TYPE_1__* family; struct device* hwmon; } ;
struct w1_family_ops {int (* add_slave ) (struct w1_slave*) ;int /*<<< orphan*/  groups; int /*<<< orphan*/  (* remove_slave ) (struct w1_slave*) ;int /*<<< orphan*/  chip_info; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct w1_family_ops* fops; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 129 
#define  BUS_NOTIFY_DEL_DEVICE 128 
 int /*<<< orphan*/  CONFIG_HWMON ; 
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct device* hwmon_device_register_with_info (TYPE_2__*,char*,struct w1_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (struct device*) ; 
 int stub1 (struct w1_slave*) ; 
 int /*<<< orphan*/  stub2 (struct w1_slave*) ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_family_notify(unsigned long action, struct w1_slave *sl)
{
	struct w1_family_ops *fops;
	int err;

	fops = sl->family->fops;

	if (!fops)
		return 0;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		/* if the family driver needs to initialize something... */
		if (fops->add_slave) {
			err = fops->add_slave(sl);
			if (err < 0) {
				dev_err(&sl->dev,
					"add_slave() call failed. err=%d\n",
					err);
				return err;
			}
		}
		if (fops->groups) {
			err = sysfs_create_groups(&sl->dev.kobj, fops->groups);
			if (err) {
				dev_err(&sl->dev,
					"sysfs group creation failed. err=%d\n",
					err);
				return err;
			}
		}
		if (IS_REACHABLE(CONFIG_HWMON) && fops->chip_info) {
			struct device *hwmon
				= hwmon_device_register_with_info(&sl->dev,
						"w1_slave_temp", sl,
						fops->chip_info,
						NULL);
			if (IS_ERR(hwmon)) {
				dev_warn(&sl->dev,
					 "could not create hwmon device\n");
			} else {
				sl->hwmon = hwmon;
			}
		}
		break;
	case BUS_NOTIFY_DEL_DEVICE:
		if (IS_REACHABLE(CONFIG_HWMON) && fops->chip_info &&
			    sl->hwmon)
			hwmon_device_unregister(sl->hwmon);
		if (fops->remove_slave)
			sl->family->fops->remove_slave(sl);
		if (fops->groups)
			sysfs_remove_groups(&sl->dev.kobj, fops->groups);
		break;
	}
	return 0;
}