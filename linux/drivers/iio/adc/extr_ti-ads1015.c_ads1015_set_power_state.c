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
struct device {int dummy; } ;
struct ads1015_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ads1015_set_power_state(struct ads1015_data *data, bool on)
{
	int ret;
	struct device *dev = regmap_get_device(data->regmap);

	if (on) {
		ret = pm_runtime_get_sync(dev);
		if (ret < 0)
			pm_runtime_put_noidle(dev);
	} else {
		pm_runtime_mark_last_busy(dev);
		ret = pm_runtime_put_autosuspend(dev);
	}

	return ret < 0 ? ret : 0;
}