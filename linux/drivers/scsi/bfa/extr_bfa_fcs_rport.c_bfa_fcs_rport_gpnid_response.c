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
typedef  int /*<<< orphan*/  u32 ;
struct fchs_s {int dummy; } ;
struct ct_hdr_s {scalar_t__ cmd_rsp_code; int reason_code; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  fcs; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_RSP_PLD (struct bfa_fcxp_s*) ; 
#define  CT_RSN_LOGICAL_BUSY 129 
#define  CT_RSN_UNABLE_TO_PERF 128 
 scalar_t__ CT_RSP_ACCEPT ; 
 int /*<<< orphan*/  RPSM_EVENT_ACCEPTED ; 
 int /*<<< orphan*/  RPSM_EVENT_FAILED ; 
 int /*<<< orphan*/  RPSM_EVENT_TIMEOUT ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_gpnid_response(void *fcsarg, struct bfa_fcxp_s *fcxp, void *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, struct fchs_s *rsp_fchs)
{
	struct bfa_fcs_rport_s *rport = (struct bfa_fcs_rport_s *) cbarg;
	struct ct_hdr_s	*cthdr;

	bfa_trc(rport->fcs, rport->pwwn);

	cthdr = (struct ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	if (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) {
		bfa_sm_send_event(rport, RPSM_EVENT_ACCEPTED);
		return;
	}

	/*
	 * Reject Response
	 */
	switch (cthdr->reason_code) {
	case CT_RSN_LOGICAL_BUSY:
		/*
		 * Need to retry
		 */
		bfa_sm_send_event(rport, RPSM_EVENT_TIMEOUT);
		break;

	case CT_RSN_UNABLE_TO_PERF:
		/*
		 * device doesn't exist : Start timer to cleanup this later.
		 */
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		break;

	default:
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		break;
	}
}