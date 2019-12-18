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
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct adv748x_hdmi {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ adv748x_hdmi_has_signal (struct adv748x_state*) ; 
 struct adv748x_state* adv748x_hdmi_to_state (struct adv748x_hdmi*) ; 
 struct adv748x_hdmi* adv748x_sd_to_hdmi (struct v4l2_subdev*) ; 
 int adv748x_tx_power (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adv_dbg (struct adv748x_state*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_hdmi_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	struct adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	int ret;

	mutex_lock(&state->mutex);

	ret = adv748x_tx_power(hdmi->tx, enable);
	if (ret)
		goto done;

	if (adv748x_hdmi_has_signal(state))
		adv_dbg(state, "Detected HDMI signal\n");
	else
		adv_dbg(state, "Couldn't detect HDMI video signal\n");

done:
	mutex_unlock(&state->mutex);
	return ret;
}