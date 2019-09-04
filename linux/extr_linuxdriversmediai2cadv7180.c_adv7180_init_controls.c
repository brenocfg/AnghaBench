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
struct TYPE_8__ {int error; } ;
struct TYPE_7__ {TYPE_2__* ctrl_handler; } ;
struct adv7180_state {TYPE_2__ ctrl_hdl; TYPE_1__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7180_BRI_DEF ; 
 int /*<<< orphan*/  ADV7180_BRI_MAX ; 
 int /*<<< orphan*/  ADV7180_BRI_MIN ; 
 int /*<<< orphan*/  ADV7180_CON_DEF ; 
 int /*<<< orphan*/  ADV7180_CON_MAX ; 
 int /*<<< orphan*/  ADV7180_CON_MIN ; 
 int /*<<< orphan*/  ADV7180_HUE_DEF ; 
 int /*<<< orphan*/  ADV7180_HUE_MAX ; 
 int /*<<< orphan*/  ADV7180_HUE_MIN ; 
 int /*<<< orphan*/  ADV7180_SAT_DEF ; 
 int /*<<< orphan*/  ADV7180_SAT_MAX ; 
 int /*<<< orphan*/  ADV7180_SAT_MIN ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  adv7180_ctrl_fast_switch ; 
 int /*<<< orphan*/  adv7180_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7180_init_controls(struct adv7180_state *state)
{
	v4l2_ctrl_handler_init(&state->ctrl_hdl, 4);

	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, ADV7180_BRI_MIN,
			  ADV7180_BRI_MAX, 1, ADV7180_BRI_DEF);
	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_CONTRAST, ADV7180_CON_MIN,
			  ADV7180_CON_MAX, 1, ADV7180_CON_DEF);
	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_SATURATION, ADV7180_SAT_MIN,
			  ADV7180_SAT_MAX, 1, ADV7180_SAT_DEF);
	v4l2_ctrl_new_std(&state->ctrl_hdl, &adv7180_ctrl_ops,
			  V4L2_CID_HUE, ADV7180_HUE_MIN,
			  ADV7180_HUE_MAX, 1, ADV7180_HUE_DEF);
	v4l2_ctrl_new_custom(&state->ctrl_hdl, &adv7180_ctrl_fast_switch, NULL);

	state->sd.ctrl_handler = &state->ctrl_hdl;
	if (state->ctrl_hdl.error) {
		int err = state->ctrl_hdl.error;

		v4l2_ctrl_handler_free(&state->ctrl_hdl);
		return err;
	}
	v4l2_ctrl_handler_setup(&state->ctrl_hdl);

	return 0;
}