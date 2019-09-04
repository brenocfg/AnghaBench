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
struct ad5820_device {int power_count; int /*<<< orphan*/  power_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ad5820_power_off (struct ad5820_device*,int) ; 
 int ad5820_power_on (struct ad5820_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ad5820_device* to_ad5820_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int
ad5820_set_power(struct v4l2_subdev *subdev, int on)
{
	struct ad5820_device *coil = to_ad5820_device(subdev);
	int ret = 0;

	mutex_lock(&coil->power_lock);

	/*
	 * If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (coil->power_count == !on) {
		ret = on ? ad5820_power_on(coil, true) :
			ad5820_power_off(coil, true);
		if (ret < 0)
			goto done;
	}

	/* Update the power count. */
	coil->power_count += on ? 1 : -1;
	WARN_ON(coil->power_count < 0);

done:
	mutex_unlock(&coil->power_lock);
	return ret;
}