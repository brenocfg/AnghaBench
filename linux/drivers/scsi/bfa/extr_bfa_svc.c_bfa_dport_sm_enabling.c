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
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ rsp; } ;
struct bfa_dport_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  test_state; TYPE_2__ i2hmsg; int /*<<< orphan*/  result; } ;
struct bfa_diag_dport_result_s {int dummy; } ;
typedef  enum bfa_dport_sm_event { ____Placeholder_bfa_dport_sm_event } bfa_dport_sm_event ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DPORT_OPMODE_AUTO ; 
#define  BFA_DPORT_SM_FWRSP 130 
#define  BFA_DPORT_SM_HWFAIL 129 
#define  BFA_DPORT_SM_REQFAIL 128 
 int /*<<< orphan*/  BFA_DPORT_ST_DISABLED ; 
 int /*<<< orphan*/  BFA_DPORT_ST_INP ; 
 int /*<<< orphan*/  BFA_DPORT_ST_NO_SFP ; 
 int /*<<< orphan*/  BFA_STATUS_DPORT_INV_SFP ; 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  bfa_cb_fcdiag_dport (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_dport_result_start (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_dport_sm_disabled ; 
 int /*<<< orphan*/  bfa_dport_sm_enabled ; 
 int /*<<< orphan*/  bfa_fcport_dportdisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_dport_sm_enabling(struct bfa_dport_s *dport, enum bfa_dport_sm_event event)
{
	bfa_trc(dport->bfa, event);

	switch (event) {
	case BFA_DPORT_SM_FWRSP:
		memset(&dport->result, 0,
				sizeof(struct bfa_diag_dport_result_s));
		if (dport->i2hmsg.rsp.status == BFA_STATUS_DPORT_INV_SFP) {
			dport->test_state = BFA_DPORT_ST_NO_SFP;
		} else {
			dport->test_state = BFA_DPORT_ST_INP;
			bfa_dport_result_start(dport, BFA_DPORT_OPMODE_AUTO);
		}
		bfa_sm_set_state(dport, bfa_dport_sm_enabled);
		break;

	case BFA_DPORT_SM_REQFAIL:
		dport->test_state = BFA_DPORT_ST_DISABLED;
		bfa_fcport_dportdisable(dport->bfa);
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		break;

	case BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_FAILED);
		break;

	default:
		bfa_sm_fault(dport->bfa, event);
	}
}