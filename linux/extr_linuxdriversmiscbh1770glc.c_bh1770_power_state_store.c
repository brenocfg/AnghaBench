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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bh1770_chip {int lux_wait_result; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lux_rate_index; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_ENABLE ; 
 int /*<<< orphan*/  BH1770_LUX_DEF_THRES ; 
 size_t bh1770_lux_interrupt_control (struct bh1770_chip*,int /*<<< orphan*/ ) ; 
 size_t bh1770_lux_rate (struct bh1770_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh1770_lux_update_thresholds (struct bh1770_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh1770_prox_mode_control (struct bh1770_chip*) ; 
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 size_t kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 

__attribute__((used)) static ssize_t bh1770_power_state_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	unsigned long value;
	ssize_t ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	mutex_lock(&chip->mutex);
	if (value) {
		pm_runtime_get_sync(dev);

		ret = bh1770_lux_rate(chip, chip->lux_rate_index);
		if (ret < 0) {
			pm_runtime_put(dev);
			goto leave;
		}

		ret = bh1770_lux_interrupt_control(chip, BH1770_ENABLE);
		if (ret < 0) {
			pm_runtime_put(dev);
			goto leave;
		}

		/* This causes interrupt after the next measurement cycle */
		bh1770_lux_update_thresholds(chip, BH1770_LUX_DEF_THRES,
					BH1770_LUX_DEF_THRES);
		/* Inform that we are waiting for a result from ALS */
		chip->lux_wait_result = true;
		bh1770_prox_mode_control(chip);
	} else if (!pm_runtime_suspended(dev)) {
		pm_runtime_put(dev);
	}
	ret = count;
leave:
	mutex_unlock(&chip->mutex);
	return ret;
}