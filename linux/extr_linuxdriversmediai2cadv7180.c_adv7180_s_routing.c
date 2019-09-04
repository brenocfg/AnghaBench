#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv7180_state {int input; int /*<<< orphan*/  mutex; TYPE_1__* chip_info; } ;
struct TYPE_2__ {int valid_input_mask; int (* select_input ) (struct adv7180_state*,int) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct adv7180_state*,int) ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7180_s_routing(struct v4l2_subdev *sd, u32 input,
			     u32 output, u32 config)
{
	struct adv7180_state *state = to_state(sd);
	int ret = mutex_lock_interruptible(&state->mutex);

	if (ret)
		return ret;

	if (input > 31 || !(BIT(input) & state->chip_info->valid_input_mask)) {
		ret = -EINVAL;
		goto out;
	}

	ret = state->chip_info->select_input(state, input);

	if (ret == 0)
		state->input = input;
out:
	mutex_unlock(&state->mutex);
	return ret;
}