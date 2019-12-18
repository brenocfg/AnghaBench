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
struct platform_device {int id; } ;
struct nvec_power {int /*<<< orphan*/  notifier; int /*<<< orphan*/  nvec; int /*<<< orphan*/  poller; } ;

/* Variables and functions */
#define  AC 129 
#define  BAT 128 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvec_bat_psy ; 
 int /*<<< orphan*/  nvec_psy ; 
 int /*<<< orphan*/  nvec_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvec_power* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvec_power_remove(struct platform_device *pdev)
{
	struct nvec_power *power = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&power->poller);
	nvec_unregister_notifier(power->nvec, &power->notifier);
	switch (pdev->id) {
	case AC:
		power_supply_unregister(nvec_psy);
		break;
	case BAT:
		power_supply_unregister(nvec_bat_psy);
	}

	return 0;
}