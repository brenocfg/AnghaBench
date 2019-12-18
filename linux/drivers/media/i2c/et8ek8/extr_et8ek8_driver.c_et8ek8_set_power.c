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
struct et8ek8_sensor {int power_count; int /*<<< orphan*/  power_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __et8ek8_set_power (struct et8ek8_sensor*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct et8ek8_sensor* to_et8ek8_sensor (struct v4l2_subdev*) ; 

__attribute__((used)) static int et8ek8_set_power(struct v4l2_subdev *subdev, int on)
{
	struct et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	int ret = 0;

	mutex_lock(&sensor->power_lock);

	/* If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (sensor->power_count == !on) {
		ret = __et8ek8_set_power(sensor, !!on);
		if (ret < 0)
			goto done;
	}

	/* Update the power count. */
	sensor->power_count += on ? 1 : -1;
	WARN_ON(sensor->power_count < 0);

done:
	mutex_unlock(&sensor->power_lock);

	return ret;
}