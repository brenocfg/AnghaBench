#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct adv748x_state {int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {int error; int /*<<< orphan*/ * lock; } ;
struct TYPE_7__ {TYPE_2__* ctrl_handler; } ;
struct adv748x_hdmi {TYPE_2__ ctrl_hdl; TYPE_1__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CP_BRI_DEF ; 
 int /*<<< orphan*/  ADV748X_CP_BRI_MAX ; 
 int /*<<< orphan*/  ADV748X_CP_BRI_MIN ; 
 int /*<<< orphan*/  ADV748X_CP_CON_DEF ; 
 int /*<<< orphan*/  ADV748X_CP_CON_MAX ; 
 int /*<<< orphan*/  ADV748X_CP_CON_MIN ; 
 int /*<<< orphan*/  ADV748X_CP_HUE_DEF ; 
 int /*<<< orphan*/  ADV748X_CP_HUE_MAX ; 
 int /*<<< orphan*/  ADV748X_CP_HUE_MIN ; 
 int /*<<< orphan*/  ADV748X_CP_SAT_DEF ; 
 int /*<<< orphan*/  ADV748X_CP_SAT_MAX ; 
 int /*<<< orphan*/  ADV748X_CP_SAT_MIN ; 
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  adv748x_hdmi_ctrl_ops ; 
 struct adv748x_state* adv748x_hdmi_to_state (struct adv748x_hdmi*) ; 
 int /*<<< orphan*/  hdmi_ctrl_patgen_menu ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_hdmi_init_controls(struct adv748x_hdmi *hdmi)
{
	struct adv748x_state *state = adv748x_hdmi_to_state(hdmi);

	v4l2_ctrl_handler_init(&hdmi->ctrl_hdl, 5);

	/* Use our mutex for the controls */
	hdmi->ctrl_hdl.lock = &state->mutex;

	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, ADV748X_CP_BRI_MIN,
			  ADV748X_CP_BRI_MAX, 1, ADV748X_CP_BRI_DEF);
	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_CONTRAST, ADV748X_CP_CON_MIN,
			  ADV748X_CP_CON_MAX, 1, ADV748X_CP_CON_DEF);
	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_SATURATION, ADV748X_CP_SAT_MIN,
			  ADV748X_CP_SAT_MAX, 1, ADV748X_CP_SAT_DEF);
	v4l2_ctrl_new_std(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
			  V4L2_CID_HUE, ADV748X_CP_HUE_MIN,
			  ADV748X_CP_HUE_MAX, 1, ADV748X_CP_HUE_DEF);

	/*
	 * Todo: V4L2_CID_DV_RX_POWER_PRESENT should also be supported when
	 * interrupts are handled correctly
	 */

	v4l2_ctrl_new_std_menu_items(&hdmi->ctrl_hdl, &adv748x_hdmi_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(hdmi_ctrl_patgen_menu) - 1,
				     0, 0, hdmi_ctrl_patgen_menu);

	hdmi->sd.ctrl_handler = &hdmi->ctrl_hdl;
	if (hdmi->ctrl_hdl.error) {
		v4l2_ctrl_handler_free(&hdmi->ctrl_hdl);
		return hdmi->ctrl_hdl.error;
	}

	return v4l2_ctrl_handler_setup(&hdmi->ctrl_hdl);
}