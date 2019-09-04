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
struct mt9v032 {int power_count; int /*<<< orphan*/  power_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __mt9v032_set_power (struct mt9v032*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9v032* to_mt9v032 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v032_set_power(struct v4l2_subdev *subdev, int on)
{
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);
	int ret = 0;

	mutex_lock(&mt9v032->power_lock);

	/* If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (mt9v032->power_count == !on) {
		ret = __mt9v032_set_power(mt9v032, !!on);
		if (ret < 0)
			goto done;
	}

	/* Update the power count. */
	mt9v032->power_count += on ? 1 : -1;
	WARN_ON(mt9v032->power_count < 0);

done:
	mutex_unlock(&mt9v032->power_lock);
	return ret;
}