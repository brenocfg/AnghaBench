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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ALC_EN ; 
 int ALC_HOLD ; 
 int EINVAL ; 
 int /*<<< orphan*/  R17 ; 
#define  V4L2_CID_AUDIO_BALANCE 131 
#define  V4L2_CID_AUDIO_LOUDNESS 130 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  wm8775_set_audio (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8775_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8775_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_AUDIO_BALANCE:
		wm8775_set_audio(sd, 0);
		return 0;
	case V4L2_CID_AUDIO_LOUDNESS:
		wm8775_write(sd, R17, (ctrl->val ? ALC_EN : 0) | ALC_HOLD);
		return 0;
	}
	return -EINVAL;
}