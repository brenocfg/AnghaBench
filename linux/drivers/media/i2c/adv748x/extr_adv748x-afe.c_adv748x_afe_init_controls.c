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
struct adv748x_afe {TYPE_2__ ctrl_hdl; TYPE_1__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_SDP_BRI_DEF ; 
 int /*<<< orphan*/  ADV748X_SDP_BRI_MAX ; 
 int /*<<< orphan*/  ADV748X_SDP_BRI_MIN ; 
 int /*<<< orphan*/  ADV748X_SDP_CON_DEF ; 
 int /*<<< orphan*/  ADV748X_SDP_CON_MAX ; 
 int /*<<< orphan*/  ADV748X_SDP_CON_MIN ; 
 int /*<<< orphan*/  ADV748X_SDP_HUE_DEF ; 
 int /*<<< orphan*/  ADV748X_SDP_HUE_MAX ; 
 int /*<<< orphan*/  ADV748X_SDP_HUE_MIN ; 
 int /*<<< orphan*/  ADV748X_SDP_SAT_DEF ; 
 int /*<<< orphan*/  ADV748X_SDP_SAT_MAX ; 
 int /*<<< orphan*/  ADV748X_SDP_SAT_MIN ; 
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  adv748x_afe_ctrl_ops ; 
 struct adv748x_state* adv748x_afe_to_state (struct adv748x_afe*) ; 
 int /*<<< orphan*/  afe_ctrl_frp_menu ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_afe_init_controls(struct adv748x_afe *afe)
{
	struct adv748x_state *state = adv748x_afe_to_state(afe);

	v4l2_ctrl_handler_init(&afe->ctrl_hdl, 5);

	/* Use our mutex for the controls */
	afe->ctrl_hdl.lock = &state->mutex;

	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, ADV748X_SDP_BRI_MIN,
			  ADV748X_SDP_BRI_MAX, 1, ADV748X_SDP_BRI_DEF);
	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_CONTRAST, ADV748X_SDP_CON_MIN,
			  ADV748X_SDP_CON_MAX, 1, ADV748X_SDP_CON_DEF);
	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_SATURATION, ADV748X_SDP_SAT_MIN,
			  ADV748X_SDP_SAT_MAX, 1, ADV748X_SDP_SAT_DEF);
	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_HUE, ADV748X_SDP_HUE_MIN,
			  ADV748X_SDP_HUE_MAX, 1, ADV748X_SDP_HUE_DEF);

	v4l2_ctrl_new_std_menu_items(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(afe_ctrl_frp_menu) - 1,
				     0, 0, afe_ctrl_frp_menu);

	afe->sd.ctrl_handler = &afe->ctrl_hdl;
	if (afe->ctrl_hdl.error) {
		v4l2_ctrl_handler_free(&afe->ctrl_hdl);
		return afe->ctrl_hdl.error;
	}

	return v4l2_ctrl_handler_setup(&afe->ctrl_hdl);
}