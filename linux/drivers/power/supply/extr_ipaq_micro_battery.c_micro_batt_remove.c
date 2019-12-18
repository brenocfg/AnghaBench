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
struct platform_device {int dummy; } ;
struct micro_battery {int /*<<< orphan*/  wq; int /*<<< orphan*/  update; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  micro_ac_power ; 
 int /*<<< orphan*/  micro_batt_power ; 
 struct micro_battery* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int micro_batt_remove(struct platform_device *pdev)

{
	struct micro_battery *mb = platform_get_drvdata(pdev);

	power_supply_unregister(micro_ac_power);
	power_supply_unregister(micro_batt_power);
	cancel_delayed_work_sync(&mb->update);
	destroy_workqueue(mb->wq);

	return 0;
}