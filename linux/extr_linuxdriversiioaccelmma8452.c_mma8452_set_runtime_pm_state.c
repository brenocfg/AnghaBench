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
struct i2c_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mma8452_set_runtime_pm_state(struct i2c_client *client, bool on)
{
#ifdef CONFIG_PM
	int ret;

	if (on) {
		ret = pm_runtime_get_sync(&client->dev);
	} else {
		pm_runtime_mark_last_busy(&client->dev);
		ret = pm_runtime_put_autosuspend(&client->dev);
	}

	if (ret < 0) {
		dev_err(&client->dev,
			"failed to change power state to %d\n", on);
		if (on)
			pm_runtime_put_noidle(&client->dev);

		return ret;
	}
#endif

	return 0;
}