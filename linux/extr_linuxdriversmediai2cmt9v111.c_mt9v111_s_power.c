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
struct v4l2_subdev {int dummy; } ;
struct mt9v111_dev {int pwr_count; int /*<<< orphan*/  pwr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __mt9v111_power_off (struct v4l2_subdev*) ; 
 int __mt9v111_power_on (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9v111_dev* sd_to_mt9v111 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v111_s_power(struct v4l2_subdev *sd, int on)
{
	struct mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	int pwr_count;
	int ret = 0;

	mutex_lock(&mt9v111->pwr_mutex);

	/*
	 * Make sure we're transitioning from 0 to 1, or viceversa,
	 * before actually changing the power state.
	 */
	pwr_count = mt9v111->pwr_count;
	pwr_count += on ? 1 : -1;
	if (pwr_count == !!on) {
		ret = on ? __mt9v111_power_on(sd) :
			   __mt9v111_power_off(sd);
		if (!ret)
			/* All went well, updated power counter. */
			mt9v111->pwr_count = pwr_count;

		mutex_unlock(&mt9v111->pwr_mutex);

		return ret;
	}

	/*
	 * Update power counter to keep track of how many nested calls we
	 * received.
	 */
	WARN_ON(pwr_count < 0 || pwr_count > 1);
	mt9v111->pwr_count = pwr_count;

	mutex_unlock(&mt9v111->pwr_mutex);

	return ret;
}