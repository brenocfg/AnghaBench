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
struct isl29028_chip {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29028_set_pm_runtime_busy(struct isl29028_chip *chip, bool on)
{
	struct device *dev = regmap_get_device(chip->regmap);
	int ret;

	if (on) {
		ret = pm_runtime_get_sync(dev);
		if (ret < 0)
			pm_runtime_put_noidle(dev);
	} else {
		pm_runtime_mark_last_busy(dev);
		ret = pm_runtime_put_autosuspend(dev);
	}

	return ret;
}