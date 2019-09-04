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
struct v4l2_ctrl {int id; int val; } ;
struct saa711x_state {TYPE_2__* gain; TYPE_1__* agc; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R_0A_LUMA_BRIGHT_CNTL ; 
 int /*<<< orphan*/  R_0B_LUMA_CONTRAST_CNTL ; 
 int /*<<< orphan*/  R_0C_CHROMA_SAT_CNTL ; 
 int /*<<< orphan*/  R_0D_CHROMA_HUE_CNTL ; 
 int /*<<< orphan*/  R_0F_CHROMA_GAIN_CNTL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CHROMA_AGC 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa711x_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct saa711x_state *state = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		saa711x_write(sd, R_0A_LUMA_BRIGHT_CNTL, ctrl->val);
		break;

	case V4L2_CID_CONTRAST:
		saa711x_write(sd, R_0B_LUMA_CONTRAST_CNTL, ctrl->val);
		break;

	case V4L2_CID_SATURATION:
		saa711x_write(sd, R_0C_CHROMA_SAT_CNTL, ctrl->val);
		break;

	case V4L2_CID_HUE:
		saa711x_write(sd, R_0D_CHROMA_HUE_CNTL, ctrl->val);
		break;

	case V4L2_CID_CHROMA_AGC:
		/* chroma gain cluster */
		if (state->agc->val)
			saa711x_write(sd, R_0F_CHROMA_GAIN_CNTL, state->gain->val);
		else
			saa711x_write(sd, R_0F_CHROMA_GAIN_CNTL, state->gain->val | 0x80);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}