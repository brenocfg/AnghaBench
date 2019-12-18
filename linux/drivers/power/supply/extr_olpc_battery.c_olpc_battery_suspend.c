#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct olpc_battery_data {TYPE_2__* olpc_bat; TYPE_1__* olpc_ac; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EC_SCI_SRC_ACPWR ; 
 int EC_SCI_SRC_BATERR ; 
 int EC_SCI_SRC_BATSOC ; 
 int EC_SCI_SRC_BATTERY ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  olpc_ec_wakeup_clear (int) ; 
 int /*<<< orphan*/  olpc_ec_wakeup_set (int) ; 
 struct olpc_battery_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int olpc_battery_suspend(struct platform_device *pdev,
				pm_message_t state)
{
	struct olpc_battery_data *data = platform_get_drvdata(pdev);

	if (device_may_wakeup(&data->olpc_ac->dev))
		olpc_ec_wakeup_set(EC_SCI_SRC_ACPWR);
	else
		olpc_ec_wakeup_clear(EC_SCI_SRC_ACPWR);

	if (device_may_wakeup(&data->olpc_bat->dev))
		olpc_ec_wakeup_set(EC_SCI_SRC_BATTERY | EC_SCI_SRC_BATSOC
				   | EC_SCI_SRC_BATERR);
	else
		olpc_ec_wakeup_clear(EC_SCI_SRC_BATTERY | EC_SCI_SRC_BATSOC
				     | EC_SCI_SRC_BATERR);

	return 0;
}