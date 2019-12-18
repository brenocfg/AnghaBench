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
typedef  int /*<<< orphan*/  u16 ;
struct gb_vibrator_device {int /*<<< orphan*/  delayed_work; TYPE_1__* connection; } ;
struct gb_bundle {int dummy; } ;
struct TYPE_2__ {struct gb_bundle* bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_VIBRATOR_TYPE_ON ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int gb_operation_sync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turn_off (struct gb_vibrator_device*) ; 

__attribute__((used)) static int turn_on(struct gb_vibrator_device *vib, u16 timeout_ms)
{
	struct gb_bundle *bundle = vib->connection->bundle;
	int ret;

	ret = gb_pm_runtime_get_sync(bundle);
	if (ret)
		return ret;

	/* Vibrator was switched ON earlier */
	if (cancel_delayed_work_sync(&vib->delayed_work))
		turn_off(vib);

	ret = gb_operation_sync(vib->connection, GB_VIBRATOR_TYPE_ON,
				NULL, 0, NULL, 0);
	if (ret) {
		gb_pm_runtime_put_autosuspend(bundle);
		return ret;
	}

	schedule_delayed_work(&vib->delayed_work, msecs_to_jiffies(timeout_ms));

	return 0;
}