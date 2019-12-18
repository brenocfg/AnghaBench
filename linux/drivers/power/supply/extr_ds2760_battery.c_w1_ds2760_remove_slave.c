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
struct w1_slave {struct ds2760_device_info* family_data; } ;
struct ds2760_device_info {int /*<<< orphan*/  bat; int /*<<< orphan*/  monitor_wqueue; int /*<<< orphan*/  set_charged_work; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  pm_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void w1_ds2760_remove_slave(struct w1_slave *sl)
{
	struct ds2760_device_info *di = sl->family_data;

	unregister_pm_notifier(&di->pm_notifier);
	cancel_delayed_work_sync(&di->monitor_work);
	cancel_delayed_work_sync(&di->set_charged_work);
	destroy_workqueue(di->monitor_wqueue);
	power_supply_unregister(di->bat);
}