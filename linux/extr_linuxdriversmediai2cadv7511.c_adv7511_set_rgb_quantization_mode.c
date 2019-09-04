#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int val; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;
struct adv7511_state {scalar_t__ fmt_code; TYPE_2__ dv_timings; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_RGB888_1X24 ; 
 int V4L2_DV_FL_IS_CE_VIDEO ; 
#define  V4L2_DV_RGB_RANGE_AUTO 130 
#define  V4L2_DV_RGB_RANGE_FULL 129 
#define  V4L2_DV_RGB_RANGE_LIMITED 128 
 int /*<<< orphan*/  adv7511_csc_rgb_full2limit (struct v4l2_subdev*,int) ; 
 struct adv7511_state* get_adv7511_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void adv7511_set_rgb_quantization_mode(struct v4l2_subdev *sd, struct v4l2_ctrl *ctrl)
{
	struct adv7511_state *state = get_adv7511_state(sd);

	/* Only makes sense for RGB formats */
	if (state->fmt_code != MEDIA_BUS_FMT_RGB888_1X24) {
		/* so just keep quantization */
		adv7511_csc_rgb_full2limit(sd, false);
		return;
	}

	switch (ctrl->val) {
	case V4L2_DV_RGB_RANGE_AUTO:
		/* automatic */
		if (state->dv_timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) {
			/* CE format, RGB limited range (16-235) */
			adv7511_csc_rgb_full2limit(sd, true);
		} else {
			/* not CE format, RGB full range (0-255) */
			adv7511_csc_rgb_full2limit(sd, false);
		}
		break;
	case V4L2_DV_RGB_RANGE_LIMITED:
		/* RGB limited range (16-235) */
		adv7511_csc_rgb_full2limit(sd, true);
		break;
	case V4L2_DV_RGB_RANGE_FULL:
		/* RGB full range (0-255) */
		adv7511_csc_rgb_full2limit(sd, false);
		break;
	}
}