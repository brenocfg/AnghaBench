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
struct v4l2_ctrl {int id; int val; int /*<<< orphan*/  handler; } ;
struct si476x_radio {int /*<<< orphan*/  core; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* phase_div_status ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  phase_diversity; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  SI476X_PHDIV_STATUS_LINK_LOCKED (int) ; 
#define  V4L2_CID_SI476X_INTERCHIP_LINK 128 
 int /*<<< orphan*/  si476x_core_has_diversity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si476x_core_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si476x_core_unlock (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 struct si476x_radio* v4l2_ctrl_handler_to_radio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si476x_radio_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	int retval;
	struct si476x_radio *radio = v4l2_ctrl_handler_to_radio(ctrl->handler);

	si476x_core_lock(radio->core);

	switch (ctrl->id) {
	case V4L2_CID_SI476X_INTERCHIP_LINK:
		if (si476x_core_has_diversity(radio->core)) {
			if (radio->ops->phase_diversity) {
				retval = radio->ops->phase_div_status(radio->core);
				if (retval < 0)
					break;

				ctrl->val = !!SI476X_PHDIV_STATUS_LINK_LOCKED(retval);
				retval = 0;
				break;
			} else {
				retval = -ENOTTY;
				break;
			}
		}
		retval = -EINVAL;
		break;
	default:
		retval = -EINVAL;
		break;
	}
	si476x_core_unlock(radio->core);
	return retval;

}