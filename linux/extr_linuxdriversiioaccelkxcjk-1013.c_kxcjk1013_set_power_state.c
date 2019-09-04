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
struct kxcjk1013_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int kxcjk1013_set_power_state(struct kxcjk1013_data *data, bool on)
{
#ifdef CONFIG_PM
	int ret;

	if (on)
		ret = pm_runtime_get_sync(&data->client->dev);
	else {
		pm_runtime_mark_last_busy(&data->client->dev);
		ret = pm_runtime_put_autosuspend(&data->client->dev);
	}
	if (ret < 0) {
		dev_err(&data->client->dev,
			"Failed: kxcjk1013_set_power_state for %d\n", on);
		if (on)
			pm_runtime_put_noidle(&data->client->dev);
		return ret;
	}
#endif

	return 0;
}