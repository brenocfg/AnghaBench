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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct s5k6aa {int power; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __s5k6aa_power_off (struct s5k6aa*) ; 
 int __s5k6aa_power_on (struct s5k6aa*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5k6aa_initialize_isp (struct v4l2_subdev*) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_set_power(struct v4l2_subdev *sd, int on)
{
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	int ret = 0;

	mutex_lock(&s5k6aa->lock);

	if (s5k6aa->power == !on) {
		if (on) {
			ret = __s5k6aa_power_on(s5k6aa);
			if (!ret)
				ret = s5k6aa_initialize_isp(sd);
		} else {
			ret = __s5k6aa_power_off(s5k6aa);
		}

		if (!ret)
			s5k6aa->power += on ? 1 : -1;
	}

	mutex_unlock(&s5k6aa->lock);

	if (!on || ret || s5k6aa->power != 1)
		return ret;

	return v4l2_ctrl_handler_setup(sd->ctrl_handler);
}