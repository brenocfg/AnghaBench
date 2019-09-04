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
struct v4l2_ctrl {int id; } ;
struct saa711x_state {TYPE_2__* gain; TYPE_1__* agc; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_0F_CHROMA_GAIN_CNTL ; 
#define  V4L2_CID_CHROMA_AGC 128 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa711x_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct saa711x_state *state = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_CHROMA_AGC:
		/* chroma gain cluster */
		if (state->agc->val)
			state->gain->val =
				saa711x_read(sd, R_0F_CHROMA_GAIN_CNTL) & 0x7f;
		break;
	}
	return 0;
}