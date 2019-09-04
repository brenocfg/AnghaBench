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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct adv7180_state {int /*<<< orphan*/  mutex; int /*<<< orphan*/  curr_norm; scalar_t__ streaming; } ;

/* Variables and functions */
 int ADV7180_STD_AD_PAL_BG_NTSC_J_SECAM ; 
 int EBUSY ; 
 int /*<<< orphan*/  __adv7180_status (struct adv7180_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int adv7180_set_video_standard (struct adv7180_state*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 
 int v4l2_std_to_adv7180 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7180_querystd(struct v4l2_subdev *sd, v4l2_std_id *std)
{
	struct adv7180_state *state = to_state(sd);
	int err = mutex_lock_interruptible(&state->mutex);
	if (err)
		return err;

	if (state->streaming) {
		err = -EBUSY;
		goto unlock;
	}

	err = adv7180_set_video_standard(state,
			ADV7180_STD_AD_PAL_BG_NTSC_J_SECAM);
	if (err)
		goto unlock;

	msleep(100);
	__adv7180_status(state, NULL, std);

	err = v4l2_std_to_adv7180(state->curr_norm);
	if (err < 0)
		goto unlock;

	err = adv7180_set_video_standard(state, err);

unlock:
	mutex_unlock(&state->mutex);
	return err;
}