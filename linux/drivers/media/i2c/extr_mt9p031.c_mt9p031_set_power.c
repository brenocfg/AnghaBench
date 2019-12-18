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
struct mt9p031 {int power_count; int /*<<< orphan*/  power_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __mt9p031_set_power (struct mt9p031*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9p031* to_mt9p031 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9p031_set_power(struct v4l2_subdev *subdev, int on)
{
	struct mt9p031 *mt9p031 = to_mt9p031(subdev);
	int ret = 0;

	mutex_lock(&mt9p031->power_lock);

	/* If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (mt9p031->power_count == !on) {
		ret = __mt9p031_set_power(mt9p031, !!on);
		if (ret < 0)
			goto out;
	}

	/* Update the power count. */
	mt9p031->power_count += on ? 1 : -1;
	WARN_ON(mt9p031->power_count < 0);

out:
	mutex_unlock(&mt9p031->power_lock);
	return ret;
}