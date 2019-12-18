#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct power_supply {int removing; TYPE_1__ dev; int /*<<< orphan*/  deferred_register_work; int /*<<< orphan*/  changed_work; int /*<<< orphan*/  use_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  power_supply_remove_hwmon_sysfs (struct power_supply*) ; 
 int /*<<< orphan*/  power_supply_remove_triggers (struct power_supply*) ; 
 int /*<<< orphan*/  psy_unregister_cooler (struct power_supply*) ; 
 int /*<<< orphan*/  psy_unregister_thermal (struct power_supply*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void power_supply_unregister(struct power_supply *psy)
{
	WARN_ON(atomic_dec_return(&psy->use_cnt));
	psy->removing = true;
	cancel_work_sync(&psy->changed_work);
	cancel_delayed_work_sync(&psy->deferred_register_work);
	sysfs_remove_link(&psy->dev.kobj, "powers");
	power_supply_remove_hwmon_sysfs(psy);
	power_supply_remove_triggers(psy);
	psy_unregister_cooler(psy);
	psy_unregister_thermal(psy);
	device_init_wakeup(&psy->dev, false);
	device_unregister(&psy->dev);
}