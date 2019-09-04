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
typedef  int /*<<< orphan*/  u8 ;
struct kmx61_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int kmx61_set_power_state(struct kmx61_data *data, bool on, u8 device)
{
#ifdef CONFIG_PM
	int ret;

	if (device & KMX61_ACC) {
		if (on && !data->acc_ps && !data->mag_stby) {
			ret = kmx61_set_mode(data, 0, KMX61_ACC, true);
			if (ret < 0)
				return ret;
		}
		data->acc_ps = on;
	}
	if (device & KMX61_MAG) {
		if (on && !data->mag_ps && !data->acc_stby) {
			ret = kmx61_set_mode(data, 0, KMX61_MAG, true);
			if (ret < 0)
				return ret;
		}
		data->mag_ps = on;
	}

	if (on) {
		ret = pm_runtime_get_sync(&data->client->dev);
	} else {
		pm_runtime_mark_last_busy(&data->client->dev);
		ret = pm_runtime_put_autosuspend(&data->client->dev);
	}
	if (ret < 0) {
		dev_err(&data->client->dev,
			"Failed: kmx61_set_power_state for %d, ret %d\n",
			on, ret);
		if (on)
			pm_runtime_put_noidle(&data->client->dev);

		return ret;
	}
#endif
	return 0;
}