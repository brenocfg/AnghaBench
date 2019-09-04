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
typedef  unsigned long u16 ;
struct bh1770_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lux_threshold_lo; int /*<<< orphan*/  lux_threshold_hi; int /*<<< orphan*/  lux_wait_result; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long BH1770_LUX_RANGE ; 
 int EINVAL ; 
 int bh1770_lux_update_thresholds (struct bh1770_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t bh1770_set_lux_thresh(struct bh1770_chip *chip, u16 *target,
				const char *buf)
{
	unsigned long thresh;
	int ret;

	ret = kstrtoul(buf, 0, &thresh);
	if (ret)
		return ret;

	if (thresh > BH1770_LUX_RANGE)
		return -EINVAL;

	mutex_lock(&chip->mutex);
	*target = thresh;
	/*
	 * Don't update values in HW if we are still waiting for
	 * first interrupt to come after device handle open call.
	 */
	if (!chip->lux_wait_result)
		ret = bh1770_lux_update_thresholds(chip,
						chip->lux_threshold_hi,
						chip->lux_threshold_lo);
	mutex_unlock(&chip->mutex);
	return ret;

}