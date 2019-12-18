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
struct v4l2_ctrl {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct TYPE_2__ {int /*<<< orphan*/  content_type; } ;
struct tda1997x_state {TYPE_1__ avi_infoframe; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_DV_RX_IT_CONTENT_TYPE ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda1997x_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct tda1997x_state *state = to_state(sd);

	if (ctrl->id == V4L2_CID_DV_RX_IT_CONTENT_TYPE) {
		ctrl->val = state->avi_infoframe.content_type;
		return 0;
	}
	return -EINVAL;
}