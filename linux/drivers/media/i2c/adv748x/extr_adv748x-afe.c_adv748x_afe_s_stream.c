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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct adv748x_afe {int streaming; int /*<<< orphan*/  tx; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 scalar_t__ V4L2_IN_ST_NO_SIGNAL ; 
 int adv748x_afe_s_input (struct adv748x_afe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv748x_afe_status (struct adv748x_afe*,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 
 struct adv748x_afe* adv748x_sd_to_afe (struct v4l2_subdev*) ; 
 int adv748x_tx_power (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adv_dbg (struct adv748x_state*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_afe_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	struct adv748x_state *state = adv748x_afe_to_state(afe);
	u32 signal = V4L2_IN_ST_NO_SIGNAL;
	int ret;

	mutex_lock(&state->mutex);

	if (enable) {
		ret = adv748x_afe_s_input(afe, afe->input);
		if (ret)
			goto unlock;
	}

	ret = adv748x_tx_power(afe->tx, enable);
	if (ret)
		goto unlock;

	afe->streaming = enable;

	adv748x_afe_status(afe, &signal, NULL);
	if (signal != V4L2_IN_ST_NO_SIGNAL)
		adv_dbg(state, "Detected SDP signal\n");
	else
		adv_dbg(state, "Couldn't detect SDP video signal\n");

unlock:
	mutex_unlock(&state->mutex);

	return ret;
}