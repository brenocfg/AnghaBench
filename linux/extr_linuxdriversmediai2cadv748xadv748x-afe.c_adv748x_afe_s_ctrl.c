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
struct v4l2_ctrl {int id; int val; } ;
struct adv748x_state {int dummy; } ;
struct adv748x_afe {int dummy; } ;

/* Variables and functions */
 int ADV748X_SDP_BRI ; 
 int ADV748X_SDP_CON ; 
 int /*<<< orphan*/  ADV748X_SDP_DEF ; 
 int /*<<< orphan*/  ADV748X_SDP_DEF_VAL_EN ; 
 int /*<<< orphan*/  ADV748X_SDP_FRP ; 
 int /*<<< orphan*/  ADV748X_SDP_FRP_MASK ; 
 int ADV748X_SDP_HUE ; 
 int ADV748X_SDP_SD_SAT_U ; 
 int ADV748X_SDP_SD_SAT_V ; 
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_TEST_PATTERN 128 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 
 struct adv748x_afe* adv748x_ctrl_to_afe (struct v4l2_ctrl*) ; 
 int sdp_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sdp_write (struct adv748x_state*,int,int) ; 

__attribute__((used)) static int adv748x_afe_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct adv748x_afe *afe = adv748x_ctrl_to_afe(ctrl);
	struct adv748x_state *state = adv748x_afe_to_state(afe);
	bool enable;
	int ret;

	ret = sdp_write(state, 0x0e, 0x00);
	if (ret < 0)
		return ret;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ret = sdp_write(state, ADV748X_SDP_BRI, ctrl->val);
		break;
	case V4L2_CID_HUE:
		/* Hue is inverted according to HSL chart */
		ret = sdp_write(state, ADV748X_SDP_HUE, -ctrl->val);
		break;
	case V4L2_CID_CONTRAST:
		ret = sdp_write(state, ADV748X_SDP_CON, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		ret = sdp_write(state, ADV748X_SDP_SD_SAT_U, ctrl->val);
		if (ret)
			break;
		ret = sdp_write(state, ADV748X_SDP_SD_SAT_V, ctrl->val);
		break;
	case V4L2_CID_TEST_PATTERN:
		enable = !!ctrl->val;

		/* Enable/Disable Color bar test patterns */
		ret = sdp_clrset(state, ADV748X_SDP_DEF, ADV748X_SDP_DEF_VAL_EN,
				enable);
		if (ret)
			break;
		ret = sdp_clrset(state, ADV748X_SDP_FRP, ADV748X_SDP_FRP_MASK,
				enable ? ctrl->val - 1 : 0);
		break;
	default:
		return -EINVAL;
	}

	return ret;
}