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
struct adp1653_flash {int power_count; int /*<<< orphan*/  power_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __adp1653_set_power (struct adp1653_flash*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct adp1653_flash* to_adp1653_flash (struct v4l2_subdev*) ; 

__attribute__((used)) static int
adp1653_set_power(struct v4l2_subdev *subdev, int on)
{
	struct adp1653_flash *flash = to_adp1653_flash(subdev);
	int ret = 0;

	mutex_lock(&flash->power_lock);

	/* If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (flash->power_count == !on) {
		ret = __adp1653_set_power(flash, !!on);
		if (ret < 0)
			goto done;
	}

	/* Update the power count. */
	flash->power_count += on ? 1 : -1;
	WARN_ON(flash->power_count < 0);

done:
	mutex_unlock(&flash->power_lock);
	return ret;
}