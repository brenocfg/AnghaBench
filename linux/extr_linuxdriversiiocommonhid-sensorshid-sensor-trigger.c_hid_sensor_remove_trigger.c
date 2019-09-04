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
struct hid_sensor_common {int /*<<< orphan*/  trigger; int /*<<< orphan*/  work; TYPE_1__* pdev; int /*<<< orphan*/  runtime_pm_enable; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 

void hid_sensor_remove_trigger(struct hid_sensor_common *attrb)
{
	if (atomic_read(&attrb->runtime_pm_enable))
		pm_runtime_disable(&attrb->pdev->dev);

	pm_runtime_set_suspended(&attrb->pdev->dev);
	pm_runtime_put_noidle(&attrb->pdev->dev);

	cancel_work_sync(&attrb->work);
	iio_trigger_unregister(attrb->trigger);
	iio_trigger_free(attrb->trigger);
}