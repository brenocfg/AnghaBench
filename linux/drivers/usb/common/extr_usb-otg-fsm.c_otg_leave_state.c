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
struct otg_fsm {int /*<<< orphan*/  a_wait_vfall_tmout; TYPE_2__* otg; int /*<<< orphan*/  a_bidl_adis_tmout; int /*<<< orphan*/  a_suspend_req_inf; int /*<<< orphan*/  a_aidl_bdis_tmout; int /*<<< orphan*/  a_wait_bcon_tmout; int /*<<< orphan*/  a_wait_vrise_tmout; int /*<<< orphan*/  adp_prb; int /*<<< orphan*/  b_ase0_brst_tmout; int /*<<< orphan*/  b_srp_done; int /*<<< orphan*/  data_pulse; int /*<<< orphan*/  adp_sns; int /*<<< orphan*/  b_se0_srp; } ;
typedef  enum usb_otg_state { ____Placeholder_usb_otg_state } usb_otg_state ;
struct TYPE_4__ {TYPE_1__* gadget; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_request_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_AIDL_BDIS ; 
 int /*<<< orphan*/  A_BIDL_ADIS ; 
 int /*<<< orphan*/  A_WAIT_BCON ; 
 int /*<<< orphan*/  A_WAIT_ENUM ; 
 int /*<<< orphan*/  A_WAIT_VFALL ; 
 int /*<<< orphan*/  A_WAIT_VRISE ; 
 int /*<<< orphan*/  B_ASE0_BRST ; 
 int /*<<< orphan*/  B_SE0_SRP ; 
#define  OTG_STATE_A_HOST 140 
#define  OTG_STATE_A_IDLE 139 
#define  OTG_STATE_A_PERIPHERAL 138 
#define  OTG_STATE_A_SUSPEND 137 
#define  OTG_STATE_A_VBUS_ERR 136 
#define  OTG_STATE_A_WAIT_BCON 135 
#define  OTG_STATE_A_WAIT_VFALL 134 
#define  OTG_STATE_A_WAIT_VRISE 133 
#define  OTG_STATE_B_HOST 132 
#define  OTG_STATE_B_IDLE 131 
#define  OTG_STATE_B_PERIPHERAL 130 
#define  OTG_STATE_B_SRP_INIT 129 
#define  OTG_STATE_B_WAIT_ACON 128 
 int /*<<< orphan*/  otg_del_timer (struct otg_fsm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void otg_leave_state(struct otg_fsm *fsm, enum usb_otg_state old_state)
{
	switch (old_state) {
	case OTG_STATE_B_IDLE:
		otg_del_timer(fsm, B_SE0_SRP);
		fsm->b_se0_srp = 0;
		fsm->adp_sns = 0;
		fsm->adp_prb = 0;
		break;
	case OTG_STATE_B_SRP_INIT:
		fsm->data_pulse = 0;
		fsm->b_srp_done = 0;
		break;
	case OTG_STATE_B_PERIPHERAL:
		if (fsm->otg->gadget)
			fsm->otg->gadget->host_request_flag = 0;
		break;
	case OTG_STATE_B_WAIT_ACON:
		otg_del_timer(fsm, B_ASE0_BRST);
		fsm->b_ase0_brst_tmout = 0;
		break;
	case OTG_STATE_B_HOST:
		break;
	case OTG_STATE_A_IDLE:
		fsm->adp_prb = 0;
		break;
	case OTG_STATE_A_WAIT_VRISE:
		otg_del_timer(fsm, A_WAIT_VRISE);
		fsm->a_wait_vrise_tmout = 0;
		break;
	case OTG_STATE_A_WAIT_BCON:
		otg_del_timer(fsm, A_WAIT_BCON);
		fsm->a_wait_bcon_tmout = 0;
		break;
	case OTG_STATE_A_HOST:
		otg_del_timer(fsm, A_WAIT_ENUM);
		break;
	case OTG_STATE_A_SUSPEND:
		otg_del_timer(fsm, A_AIDL_BDIS);
		fsm->a_aidl_bdis_tmout = 0;
		fsm->a_suspend_req_inf = 0;
		break;
	case OTG_STATE_A_PERIPHERAL:
		otg_del_timer(fsm, A_BIDL_ADIS);
		fsm->a_bidl_adis_tmout = 0;
		if (fsm->otg->gadget)
			fsm->otg->gadget->host_request_flag = 0;
		break;
	case OTG_STATE_A_WAIT_VFALL:
		otg_del_timer(fsm, A_WAIT_VFALL);
		fsm->a_wait_vfall_tmout = 0;
		otg_del_timer(fsm, A_WAIT_VRISE);
		break;
	case OTG_STATE_A_VBUS_ERR:
		break;
	default:
		break;
	}
}