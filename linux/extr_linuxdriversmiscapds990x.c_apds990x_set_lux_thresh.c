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
typedef  unsigned long u32 ;
struct apds990x_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lux_wait_fresh_res; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long APDS_RANGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  apds990x_refresh_athres (struct apds990x_chip*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t apds990x_set_lux_thresh(struct apds990x_chip *chip, u32 *target,
				const char *buf)
{
	unsigned long thresh;
	int ret;

	ret = kstrtoul(buf, 0, &thresh);
	if (ret)
		return ret;

	if (thresh > APDS_RANGE)
		return -EINVAL;

	mutex_lock(&chip->mutex);
	*target = thresh;
	/*
	 * Don't update values in HW if we are still waiting for
	 * first interrupt to come after device handle open call.
	 */
	if (!chip->lux_wait_fresh_res)
		apds990x_refresh_athres(chip);
	mutex_unlock(&chip->mutex);
	return ret;

}