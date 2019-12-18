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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 132 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  set_balance (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bass (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mute (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_treble (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_volume (struct cx18*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx18_av_audio_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct cx18 *cx = v4l2_get_subdevdata(sd);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_VOLUME:
		set_volume(cx, ctrl->val);
		break;
	case V4L2_CID_AUDIO_BASS:
		set_bass(cx, ctrl->val);
		break;
	case V4L2_CID_AUDIO_TREBLE:
		set_treble(cx, ctrl->val);
		break;
	case V4L2_CID_AUDIO_BALANCE:
		set_balance(cx, ctrl->val);
		break;
	case V4L2_CID_AUDIO_MUTE:
		set_mute(cx, ctrl->val);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}