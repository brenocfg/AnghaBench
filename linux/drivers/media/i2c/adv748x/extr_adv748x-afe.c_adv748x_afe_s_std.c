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
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct adv748x_afe {int /*<<< orphan*/  curr_norm; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv748x_afe_set_video_standard (struct adv748x_state*,int) ; 
 int adv748x_afe_std (int /*<<< orphan*/ ) ; 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 
 struct adv748x_afe* adv748x_sd_to_afe (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_afe_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	struct adv748x_state *state = adv748x_afe_to_state(afe);
	int afe_std = adv748x_afe_std(std);

	if (afe_std < 0)
		return afe_std;

	mutex_lock(&state->mutex);

	adv748x_afe_set_video_standard(state, afe_std);
	afe->curr_norm = std;

	mutex_unlock(&state->mutex);

	return 0;
}