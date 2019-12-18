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
struct TYPE_4__ {int a_bidl_adis_tmout; int /*<<< orphan*/  lock; TYPE_1__* otg; int /*<<< orphan*/  protocol; } ;
struct ci_hdrc {TYPE_2__ fsm; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ OTG_STATE_A_PERIPHERAL ; 
 scalar_t__ OTG_STATE_B_PERIPHERAL ; 
 scalar_t__ OTG_STATE_UNDEFINED ; 
 int /*<<< orphan*/  PROTO_UNDEF ; 
 int /*<<< orphan*/  ci_hdrc_otg_fsm_start (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_otg_is_fsm_mode (struct ci_hdrc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ci_udc_stop_for_otg_fsm(struct ci_hdrc *ci)
{
	if (!ci_otg_is_fsm_mode(ci))
		return;

	mutex_lock(&ci->fsm.lock);
	if (ci->fsm.otg->state == OTG_STATE_A_PERIPHERAL) {
		ci->fsm.a_bidl_adis_tmout = 1;
		ci_hdrc_otg_fsm_start(ci);
	} else if (ci->fsm.otg->state == OTG_STATE_B_PERIPHERAL) {
		ci->fsm.protocol = PROTO_UNDEF;
		ci->fsm.otg->state = OTG_STATE_UNDEFINED;
	}
	mutex_unlock(&ci->fsm.lock);
}