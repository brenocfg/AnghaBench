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
struct TYPE_3__ {int state; } ;
struct TYPE_4__ {TYPE_1__ scn; } ;
struct bfa_dport_s {int /*<<< orphan*/  bfa; TYPE_2__ i2hmsg; int /*<<< orphan*/  dynamic; int /*<<< orphan*/  test_state; } ;
typedef  enum bfa_dport_sm_event { ____Placeholder_bfa_dport_sm_event } bfa_dport_sm_event ;

/* Variables and functions */
#define  BFA_DPORT_SM_DISABLE 138 
#define  BFA_DPORT_SM_HWFAIL 137 
#define  BFA_DPORT_SM_SCN 136 
#define  BFA_DPORT_SM_START 135 
 int /*<<< orphan*/  BFA_DPORT_ST_COMP ; 
 int /*<<< orphan*/  BFA_DPORT_ST_INP ; 
 int /*<<< orphan*/  BFA_DPORT_ST_NO_SFP ; 
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFI_DPORT_DISABLE ; 
 int /*<<< orphan*/  BFI_DPORT_DYN_DISABLE ; 
#define  BFI_DPORT_SCN_DDPORT_DISABLE 134 
#define  BFI_DPORT_SCN_FCPORT_DISABLE 133 
#define  BFI_DPORT_SCN_SFP_REMOVED 132 
#define  BFI_DPORT_SCN_SUBTESTSTART 131 
#define  BFI_DPORT_SCN_TESTCOMP 130 
#define  BFI_DPORT_SCN_TESTSKIP 129 
#define  BFI_DPORT_SCN_TESTSTART 128 
 int /*<<< orphan*/  BFI_DPORT_START ; 
 int /*<<< orphan*/  bfa_dport_send_req (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_dport_sm_disabled ; 
 int /*<<< orphan*/  bfa_dport_sm_disabling ; 
 int /*<<< orphan*/  bfa_dport_sm_disabling_qwait ; 
 int /*<<< orphan*/  bfa_dport_sm_dynamic_disabling ; 
 int /*<<< orphan*/  bfa_dport_sm_dynamic_disabling_qwait ; 
 int /*<<< orphan*/  bfa_dport_sm_starting ; 
 int /*<<< orphan*/  bfa_dport_sm_starting_qwait ; 
 int /*<<< orphan*/  bfa_fcport_ddportdisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_dportdisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_dport_sm_enabled(struct bfa_dport_s *dport, enum bfa_dport_sm_event event)
{
	bfa_trc(dport->bfa, event);

	switch (event) {
	case BFA_DPORT_SM_START:
		if (bfa_dport_send_req(dport, BFI_DPORT_START))
			bfa_sm_set_state(dport, bfa_dport_sm_starting);
		else
			bfa_sm_set_state(dport, bfa_dport_sm_starting_qwait);
		break;

	case BFA_DPORT_SM_DISABLE:
		bfa_fcport_dportdisable(dport->bfa);
		if (bfa_dport_send_req(dport, BFI_DPORT_DISABLE))
			bfa_sm_set_state(dport, bfa_dport_sm_disabling);
		else
			bfa_sm_set_state(dport, bfa_dport_sm_disabling_qwait);
		break;

	case BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		break;

	case BFA_DPORT_SM_SCN:
		switch (dport->i2hmsg.scn.state) {
		case BFI_DPORT_SCN_TESTCOMP:
			dport->test_state = BFA_DPORT_ST_COMP;
			break;

		case BFI_DPORT_SCN_TESTSTART:
			dport->test_state = BFA_DPORT_ST_INP;
			break;

		case BFI_DPORT_SCN_TESTSKIP:
		case BFI_DPORT_SCN_SUBTESTSTART:
			/* no state change */
			break;

		case BFI_DPORT_SCN_SFP_REMOVED:
			dport->test_state = BFA_DPORT_ST_NO_SFP;
			break;

		case BFI_DPORT_SCN_DDPORT_DISABLE:
			bfa_fcport_ddportdisable(dport->bfa);

			if (bfa_dport_send_req(dport, BFI_DPORT_DYN_DISABLE))
				bfa_sm_set_state(dport,
					 bfa_dport_sm_dynamic_disabling);
			else
				bfa_sm_set_state(dport,
					 bfa_dport_sm_dynamic_disabling_qwait);
			break;

		case BFI_DPORT_SCN_FCPORT_DISABLE:
			bfa_fcport_ddportdisable(dport->bfa);

			bfa_sm_set_state(dport, bfa_dport_sm_disabled);
			dport->dynamic = BFA_FALSE;
			break;

		default:
			bfa_trc(dport->bfa, dport->i2hmsg.scn.state);
			bfa_sm_fault(dport->bfa, event);
		}
		break;
	default:
		bfa_sm_fault(dport->bfa, event);
	}
}