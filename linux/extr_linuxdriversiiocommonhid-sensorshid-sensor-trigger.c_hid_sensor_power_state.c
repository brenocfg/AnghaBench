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
struct hid_sensor_common {int /*<<< orphan*/  user_requested_state; } ;

/* Variables and functions */
 int _hid_sensor_power_state (struct hid_sensor_common*,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

int hid_sensor_power_state(struct hid_sensor_common *st, bool state)
{

#ifdef CONFIG_PM
	int ret;

	if (atomic_add_unless(&st->runtime_pm_enable, 1, 1))
		pm_runtime_enable(&st->pdev->dev);

	if (state) {
		atomic_inc(&st->user_requested_state);
		ret = pm_runtime_get_sync(&st->pdev->dev);
	} else {
		atomic_dec(&st->user_requested_state);
		pm_runtime_mark_last_busy(&st->pdev->dev);
		pm_runtime_use_autosuspend(&st->pdev->dev);
		ret = pm_runtime_put_autosuspend(&st->pdev->dev);
	}
	if (ret < 0) {
		if (state)
			pm_runtime_put_noidle(&st->pdev->dev);
		return ret;
	}

	return 0;
#else
	atomic_set(&st->user_requested_state, state);
	return _hid_sensor_power_state(st, state);
#endif
}