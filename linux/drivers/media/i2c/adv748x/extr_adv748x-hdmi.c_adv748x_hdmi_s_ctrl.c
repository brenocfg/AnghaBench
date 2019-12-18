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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct adv748x_state {int dummy; } ;
struct adv748x_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CP_BRI ; 
 int /*<<< orphan*/  ADV748X_CP_CON ; 
 int /*<<< orphan*/  ADV748X_CP_HUE ; 
 int /*<<< orphan*/  ADV748X_CP_PAT_GEN ; 
 int /*<<< orphan*/  ADV748X_CP_PAT_GEN_EN ; 
 int /*<<< orphan*/  ADV748X_CP_SAT ; 
 int /*<<< orphan*/  ADV748X_CP_VID_ADJ ; 
 int /*<<< orphan*/  ADV748X_CP_VID_ADJ_ENABLE ; 
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_TEST_PATTERN 128 
 struct adv748x_hdmi* adv748x_ctrl_to_hdmi (struct v4l2_ctrl*) ; 
 struct adv748x_state* adv748x_hdmi_to_state (struct adv748x_hdmi*) ; 
 int cp_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cp_write (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_hdmi_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct adv748x_hdmi *hdmi = adv748x_ctrl_to_hdmi(ctrl);
	struct adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	int ret;
	u8 pattern;

	/* Enable video adjustment first */
	ret = cp_clrset(state, ADV748X_CP_VID_ADJ,
			ADV748X_CP_VID_ADJ_ENABLE,
			ADV748X_CP_VID_ADJ_ENABLE);
	if (ret < 0)
		return ret;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ret = cp_write(state, ADV748X_CP_BRI, ctrl->val);
		break;
	case V4L2_CID_HUE:
		ret = cp_write(state, ADV748X_CP_HUE, ctrl->val);
		break;
	case V4L2_CID_CONTRAST:
		ret = cp_write(state, ADV748X_CP_CON, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		ret = cp_write(state, ADV748X_CP_SAT, ctrl->val);
		break;
	case V4L2_CID_TEST_PATTERN:
		pattern = ctrl->val;

		/* Pattern is 0-indexed. Ctrl Menu is 1-indexed */
		if (pattern) {
			pattern--;
			pattern |= ADV748X_CP_PAT_GEN_EN;
		}

		ret = cp_write(state, ADV748X_CP_PAT_GEN, pattern);

		break;
	default:
		return -EINVAL;
	}

	return ret;
}