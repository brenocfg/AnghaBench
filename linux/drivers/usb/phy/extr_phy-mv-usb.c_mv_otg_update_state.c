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
struct mv_otg_ctrl {int /*<<< orphan*/  a_clr_err; int /*<<< orphan*/  a_bus_drop; int /*<<< orphan*/  id; int /*<<< orphan*/  a_bus_req; int /*<<< orphan*/  a_sess_vld; int /*<<< orphan*/  b_conn; int /*<<< orphan*/  a_vbus_vld; int /*<<< orphan*/  a_wait_bcon_timeout; int /*<<< orphan*/  a_srp_det; int /*<<< orphan*/  b_sess_vld; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct mv_otg {TYPE_2__ phy; struct mv_otg_ctrl otg_ctrl; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_WAIT_BCON_TIMER ; 
#define  OTG_STATE_A_HOST 136 
#define  OTG_STATE_A_IDLE 135 
#define  OTG_STATE_A_VBUS_ERR 134 
#define  OTG_STATE_A_WAIT_BCON 133 
#define  OTG_STATE_A_WAIT_VFALL 132 
#define  OTG_STATE_A_WAIT_VRISE 131 
#define  OTG_STATE_B_IDLE 130 
#define  OTG_STATE_B_PERIPHERAL 129 
#define  OTG_STATE_UNDEFINED 128 
 int /*<<< orphan*/  mv_otg_cancel_timer (struct mv_otg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_otg_update_state(struct mv_otg *mvotg)
{
	struct mv_otg_ctrl *otg_ctrl = &mvotg->otg_ctrl;
	int old_state = mvotg->phy.otg->state;

	switch (old_state) {
	case OTG_STATE_UNDEFINED:
		mvotg->phy.otg->state = OTG_STATE_B_IDLE;
		/* FALL THROUGH */
	case OTG_STATE_B_IDLE:
		if (otg_ctrl->id == 0)
			mvotg->phy.otg->state = OTG_STATE_A_IDLE;
		else if (otg_ctrl->b_sess_vld)
			mvotg->phy.otg->state = OTG_STATE_B_PERIPHERAL;
		break;
	case OTG_STATE_B_PERIPHERAL:
		if (!otg_ctrl->b_sess_vld || otg_ctrl->id == 0)
			mvotg->phy.otg->state = OTG_STATE_B_IDLE;
		break;
	case OTG_STATE_A_IDLE:
		if (otg_ctrl->id)
			mvotg->phy.otg->state = OTG_STATE_B_IDLE;
		else if (!(otg_ctrl->a_bus_drop) &&
			 (otg_ctrl->a_bus_req || otg_ctrl->a_srp_det))
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VRISE;
		break;
	case OTG_STATE_A_WAIT_VRISE:
		if (otg_ctrl->a_vbus_vld)
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_BCON;
		break;
	case OTG_STATE_A_WAIT_BCON:
		if (otg_ctrl->id || otg_ctrl->a_bus_drop
		    || otg_ctrl->a_wait_bcon_timeout) {
			mv_otg_cancel_timer(mvotg, A_WAIT_BCON_TIMER);
			mvotg->otg_ctrl.a_wait_bcon_timeout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VFALL;
			otg_ctrl->a_bus_req = 0;
		} else if (!otg_ctrl->a_vbus_vld) {
			mv_otg_cancel_timer(mvotg, A_WAIT_BCON_TIMER);
			mvotg->otg_ctrl.a_wait_bcon_timeout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_VBUS_ERR;
		} else if (otg_ctrl->b_conn) {
			mv_otg_cancel_timer(mvotg, A_WAIT_BCON_TIMER);
			mvotg->otg_ctrl.a_wait_bcon_timeout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_HOST;
		}
		break;
	case OTG_STATE_A_HOST:
		if (otg_ctrl->id || !otg_ctrl->b_conn
		    || otg_ctrl->a_bus_drop)
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_BCON;
		else if (!otg_ctrl->a_vbus_vld)
			mvotg->phy.otg->state = OTG_STATE_A_VBUS_ERR;
		break;
	case OTG_STATE_A_WAIT_VFALL:
		if (otg_ctrl->id
		    || (!otg_ctrl->b_conn && otg_ctrl->a_sess_vld)
		    || otg_ctrl->a_bus_req)
			mvotg->phy.otg->state = OTG_STATE_A_IDLE;
		break;
	case OTG_STATE_A_VBUS_ERR:
		if (otg_ctrl->id || otg_ctrl->a_clr_err
		    || otg_ctrl->a_bus_drop) {
			otg_ctrl->a_clr_err = 0;
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VFALL;
		}
		break;
	default:
		break;
	}
}