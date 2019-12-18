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
struct bfa_dport_s {int /*<<< orphan*/  bfa; TYPE_2__ i2hmsg; int /*<<< orphan*/  test_state; int /*<<< orphan*/  dynamic; } ;
typedef  enum bfa_dport_sm_event { ____Placeholder_bfa_dport_sm_event } bfa_dport_sm_event ;

/* Variables and functions */
#define  BFA_DPORT_SM_DISABLE 131 
#define  BFA_DPORT_SM_ENABLE 130 
#define  BFA_DPORT_SM_HWFAIL 129 
#define  BFA_DPORT_SM_SCN 128 
 int /*<<< orphan*/  BFA_DPORT_ST_NOTSTART ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_DPORT_ENABLE ; 
 int BFI_DPORT_SCN_DDPORT_ENABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_dport_send_req (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_dport_sm_enabled ; 
 int /*<<< orphan*/  bfa_dport_sm_enabling ; 
 int /*<<< orphan*/  bfa_dport_sm_enabling_qwait ; 
 int /*<<< orphan*/  bfa_fcport_ddportenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_dportenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_dport_sm_disabled(struct bfa_dport_s *dport, enum bfa_dport_sm_event event)
{
	bfa_trc(dport->bfa, event);

	switch (event) {
	case BFA_DPORT_SM_ENABLE:
		bfa_fcport_dportenable(dport->bfa);
		if (bfa_dport_send_req(dport, BFI_DPORT_ENABLE))
			bfa_sm_set_state(dport, bfa_dport_sm_enabling);
		else
			bfa_sm_set_state(dport, bfa_dport_sm_enabling_qwait);
		break;

	case BFA_DPORT_SM_DISABLE:
		/* Already disabled */
		break;

	case BFA_DPORT_SM_HWFAIL:
		/* ignore */
		break;

	case BFA_DPORT_SM_SCN:
		if (dport->i2hmsg.scn.state ==  BFI_DPORT_SCN_DDPORT_ENABLE) {
			bfa_fcport_ddportenable(dport->bfa);
			dport->dynamic = BFA_TRUE;
			dport->test_state = BFA_DPORT_ST_NOTSTART;
			bfa_sm_set_state(dport, bfa_dport_sm_enabled);
		} else {
			bfa_trc(dport->bfa, dport->i2hmsg.scn.state);
			WARN_ON(1);
		}
		break;

	default:
		bfa_sm_fault(dport->bfa, event);
	}
}