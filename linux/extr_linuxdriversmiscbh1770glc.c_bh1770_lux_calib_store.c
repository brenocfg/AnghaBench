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
typedef  scalar_t__ u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bh1770_chip {scalar_t__ lux_calib; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lux_threshold_lo; int /*<<< orphan*/  lux_threshold_hi; scalar_t__ lux_corr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ bh1770_get_corr_value (struct bh1770_chip*) ; 
 int /*<<< orphan*/  bh1770_lux_update_thresholds (struct bh1770_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t bh1770_lux_calib_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct bh1770_chip *chip = dev_get_drvdata(dev);
	unsigned long value;
	u32 old_calib;
	u32 new_corr;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	mutex_lock(&chip->mutex);
	old_calib = chip->lux_calib;
	chip->lux_calib = value;
	new_corr = bh1770_get_corr_value(chip);
	if (new_corr == 0) {
		chip->lux_calib = old_calib;
		mutex_unlock(&chip->mutex);
		return -EINVAL;
	}
	chip->lux_corr = new_corr;
	/* Refresh thresholds on HW after changing correction value */
	bh1770_lux_update_thresholds(chip, chip->lux_threshold_hi,
				chip->lux_threshold_lo);

	mutex_unlock(&chip->mutex);

	return len;
}