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
struct pa12203001_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int pa12203001_set_power_state(struct pa12203001_data *data, bool on,
				      u8 mask)
{
#ifdef CONFIG_PM
	int ret;

	if (on && (mask & PA12203001_ALS_EN_MASK)) {
		mutex_lock(&data->lock);
		if (data->px_enabled) {
			ret = pa12203001_als_enable(data,
						    PA12203001_ALS_EN_MASK);
			if (ret < 0)
				goto err;
		} else {
			data->als_needs_enable = true;
		}
		mutex_unlock(&data->lock);
	}

	if (on && (mask & PA12203001_PX_EN_MASK)) {
		mutex_lock(&data->lock);
		if (data->als_enabled) {
			ret = pa12203001_px_enable(data, PA12203001_PX_EN_MASK);
			if (ret < 0)
				goto err;
		} else {
			data->px_needs_enable = true;
		}
		mutex_unlock(&data->lock);
	}

	if (on) {
		ret = pm_runtime_get_sync(&data->client->dev);
		if (ret < 0)
			pm_runtime_put_noidle(&data->client->dev);

	} else {
		pm_runtime_mark_last_busy(&data->client->dev);
		ret = pm_runtime_put_autosuspend(&data->client->dev);
	}

	return ret;

err:
	mutex_unlock(&data->lock);
	return ret;

#endif
	return 0;
}