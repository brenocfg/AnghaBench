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
struct TYPE_4__ {TYPE_1__* otg; scalar_t__ power_up; scalar_t__ b_sess_vld; scalar_t__ id; } ;
struct ci_hdrc {int id_event; int /*<<< orphan*/  dev; TYPE_2__ fsm; int /*<<< orphan*/  driver; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_PORTSC ; 
 int /*<<< orphan*/  OTGSC_DPIE ; 
 int /*<<< orphan*/  OTGSC_DPIS ; 
 scalar_t__ OTG_STATE_A_HOST ; 
 scalar_t__ OTG_STATE_A_IDLE ; 
 scalar_t__ OTG_STATE_B_IDLE ; 
 int PORTSC_PP ; 
 int PORTSC_W1C_BITS ; 
 int /*<<< orphan*/  ci_otg_queue_work (struct ci_hdrc*) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_otgsc (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ otg_statemachine (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

int ci_otg_fsm_work(struct ci_hdrc *ci)
{
	/*
	 * Don't do fsm transition for B device
	 * when there is no gadget class driver
	 */
	if (ci->fsm.id && !(ci->driver) &&
		ci->fsm.otg->state < OTG_STATE_A_IDLE)
		return 0;

	pm_runtime_get_sync(ci->dev);
	if (otg_statemachine(&ci->fsm)) {
		if (ci->fsm.otg->state == OTG_STATE_A_IDLE) {
			/*
			 * Further state change for cases:
			 * a_idle to b_idle; or
			 * a_idle to a_wait_vrise due to ID change(1->0), so
			 * B-dev becomes A-dev can try to start new session
			 * consequently; or
			 * a_idle to a_wait_vrise when power up
			 */
			if ((ci->fsm.id) || (ci->id_event) ||
						(ci->fsm.power_up)) {
				ci_otg_queue_work(ci);
			} else {
				/* Enable data pulse irq */
				hw_write(ci, OP_PORTSC, PORTSC_W1C_BITS |
								PORTSC_PP, 0);
				hw_write_otgsc(ci, OTGSC_DPIS, OTGSC_DPIS);
				hw_write_otgsc(ci, OTGSC_DPIE, OTGSC_DPIE);
			}
			if (ci->id_event)
				ci->id_event = false;
		} else if (ci->fsm.otg->state == OTG_STATE_B_IDLE) {
			if (ci->fsm.b_sess_vld) {
				ci->fsm.power_up = 0;
				/*
				 * Further transite to b_periphearl state
				 * when register gadget driver with vbus on
				 */
				ci_otg_queue_work(ci);
			}
		} else if (ci->fsm.otg->state == OTG_STATE_A_HOST) {
			pm_runtime_mark_last_busy(ci->dev);
			pm_runtime_put_autosuspend(ci->dev);
			return 0;
		}
	}
	pm_runtime_put_sync(ci->dev);
	return 0;
}