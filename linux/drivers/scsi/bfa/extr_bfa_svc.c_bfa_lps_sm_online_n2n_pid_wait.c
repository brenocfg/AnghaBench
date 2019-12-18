#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_lps_s {int bfa_tag; TYPE_1__* bfa; int /*<<< orphan*/  wqe; } ;
typedef  enum bfa_lps_event { ____Placeholder_bfa_lps_event } bfa_lps_event ;
struct TYPE_3__ {int /*<<< orphan*/  plog; } ;

/* Variables and functions */
#define  BFA_LPS_SM_DELETE 132 
#define  BFA_LPS_SM_LOGOUT 131 
#define  BFA_LPS_SM_OFFLINE 130 
#define  BFA_LPS_SM_RESUME 129 
#define  BFA_LPS_SM_RX_CVL 128 
 int /*<<< orphan*/  BFA_PL_EID_FIP_FCF_CVL ; 
 int /*<<< orphan*/  BFA_PL_EID_LOGO ; 
 int /*<<< orphan*/  BFA_PL_MID_LPS ; 
 int /*<<< orphan*/  bfa_lps_cvl_event (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_send_set_n2n_pid (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_sm_init ; 
 int /*<<< orphan*/  bfa_lps_sm_logowait ; 
 int /*<<< orphan*/  bfa_lps_sm_online ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfa_reqq_wcancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_lps_sm_online_n2n_pid_wait(struct bfa_lps_s *lps, enum bfa_lps_event event)
{
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	switch (event) {
	case BFA_LPS_SM_RESUME:
		bfa_sm_set_state(lps, bfa_lps_sm_online);
		bfa_lps_send_set_n2n_pid(lps);
		break;

	case BFA_LPS_SM_LOGOUT:
		bfa_sm_set_state(lps, bfa_lps_sm_logowait);
		bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
			BFA_PL_EID_LOGO, 0, "Logout");
		break;

	case BFA_LPS_SM_RX_CVL:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);

		/* Let the vport module know about this event */
		bfa_lps_cvl_event(lps);
		bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
			BFA_PL_EID_FIP_FCF_CVL, 0, "FCF Clear Virt. Link Rx");
		break;

	case BFA_LPS_SM_OFFLINE:
	case BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);
		break;

	default:
		bfa_sm_fault(lps->bfa, event);
	}
}