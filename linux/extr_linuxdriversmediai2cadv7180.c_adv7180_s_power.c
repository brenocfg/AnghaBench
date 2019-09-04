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
struct adv7180_state {int powered; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int adv7180_set_power (struct adv7180_state*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7180_s_power(struct v4l2_subdev *sd, int on)
{
	struct adv7180_state *state = to_state(sd);
	int ret;

	ret = mutex_lock_interruptible(&state->mutex);
	if (ret)
		return ret;

	ret = adv7180_set_power(state, on);
	if (ret == 0)
		state->powered = on;

	mutex_unlock(&state->mutex);
	return ret;
}