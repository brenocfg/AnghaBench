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
struct bfa_fcport_s {int use_flash_cfg; int /*<<< orphan*/  bfa; } ;
typedef  enum bfa_fcport_sm_event { ____Placeholder_bfa_fcport_sm_event } bfa_fcport_sm_event ;

/* Variables and functions */
 int BFA_FALSE ; 
#define  BFA_FCPORT_SM_DISABLE 131 
#define  BFA_FCPORT_SM_ENABLE 130 
#define  BFA_FCPORT_SM_HWFAIL 129 
#define  BFA_FCPORT_SM_START 128 
 int BFA_TRUE ; 
 int /*<<< orphan*/  bfa_fcport_send_enable (struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_sm_disabled ; 
 int /*<<< orphan*/  bfa_fcport_sm_enabling ; 
 int /*<<< orphan*/  bfa_fcport_sm_enabling_qwait ; 
 int /*<<< orphan*/  bfa_fcport_sm_iocdown ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcport_sm_uninit(struct bfa_fcport_s *fcport,
			enum bfa_fcport_sm_event event)
{
	bfa_trc(fcport->bfa, event);

	switch (event) {
	case BFA_FCPORT_SM_START:
		/*
		 * Start event after IOC is configured and BFA is started.
		 */
		fcport->use_flash_cfg = BFA_TRUE;

		if (bfa_fcport_send_enable(fcport)) {
			bfa_trc(fcport->bfa, BFA_TRUE);
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		} else {
			bfa_trc(fcport->bfa, BFA_FALSE);
			bfa_sm_set_state(fcport,
					bfa_fcport_sm_enabling_qwait);
		}
		break;

	case BFA_FCPORT_SM_ENABLE:
		/*
		 * Port is persistently configured to be in enabled state. Do
		 * not change state. Port enabling is done when START event is
		 * received.
		 */
		break;

	case BFA_FCPORT_SM_DISABLE:
		/*
		 * If a port is persistently configured to be disabled, the
		 * first event will a port disable request.
		 */
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		break;

	case BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocdown);
		break;

	default:
		bfa_sm_fault(fcport->bfa, event);
	}
}