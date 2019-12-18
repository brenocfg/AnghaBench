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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {scalar_t__ interlaced; } ;
struct v4l2_dv_timings {TYPE_1__ bt; } ;
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct adv748x_hdmi {struct v4l2_dv_timings timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CP_VID_ADJ_2 ; 
 int /*<<< orphan*/  ADV748X_CP_VID_ADJ_2_INTERLACED ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  adv748x_fill_optional_dv_timings (struct v4l2_dv_timings*) ; 
 int adv748x_hdmi_set_video_timings (struct adv748x_state*,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  adv748x_hdmi_timings_cap ; 
 struct adv748x_state* adv748x_hdmi_to_state (struct adv748x_hdmi*) ; 
 struct adv748x_hdmi* adv748x_sd_to_hdmi (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cp_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings*,struct v4l2_dv_timings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_valid_dv_timings (struct v4l2_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_hdmi_s_dv_timings(struct v4l2_subdev *sd,
				     struct v4l2_dv_timings *timings)
{
	struct adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	struct adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	int ret;

	if (!timings)
		return -EINVAL;

	if (v4l2_match_dv_timings(&hdmi->timings, timings, 0, false))
		return 0;

	if (!v4l2_valid_dv_timings(timings, &adv748x_hdmi_timings_cap,
				   NULL, NULL))
		return -ERANGE;

	adv748x_fill_optional_dv_timings(timings);

	mutex_lock(&state->mutex);

	ret = adv748x_hdmi_set_video_timings(state, timings);
	if (ret)
		goto error;

	hdmi->timings = *timings;

	cp_clrset(state, ADV748X_CP_VID_ADJ_2, ADV748X_CP_VID_ADJ_2_INTERLACED,
		  timings->bt.interlaced ?
				  ADV748X_CP_VID_ADJ_2_INTERLACED : 0);

	mutex_unlock(&state->mutex);

	return 0;

error:
	mutex_unlock(&state->mutex);
	return ret;
}