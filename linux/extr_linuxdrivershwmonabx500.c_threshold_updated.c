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
struct abx500_temp {int monitored_sensors; scalar_t__* max; scalar_t__* min; int work_active; int /*<<< orphan*/  work; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  schedule_monitor (struct abx500_temp*) ; 

__attribute__((used)) static void threshold_updated(struct abx500_temp *data)
{
	int i;
	for (i = 0; i < data->monitored_sensors; i++)
		if (data->max[i] != 0 || data->min[i] != 0) {
			schedule_monitor(data);
			return;
		}

	dev_dbg(&data->pdev->dev, "No active thresholds.\n");
	cancel_delayed_work_sync(&data->work);
	data->work_active = false;
}