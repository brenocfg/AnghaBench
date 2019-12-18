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
struct v4l2_dv_timings {int dummy; } ;
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct adv748x_hdmi {struct v4l2_dv_timings timings; } ;

/* Variables and functions */
 struct adv748x_state* adv748x_hdmi_to_state (struct adv748x_hdmi*) ; 
 struct adv748x_hdmi* adv748x_sd_to_hdmi (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_hdmi_g_dv_timings(struct v4l2_subdev *sd,
				     struct v4l2_dv_timings *timings)
{
	struct adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	struct adv748x_state *state = adv748x_hdmi_to_state(hdmi);

	mutex_lock(&state->mutex);

	*timings = hdmi->timings;

	mutex_unlock(&state->mutex);

	return 0;
}