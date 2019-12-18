#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcs_rport_s {int pwwn; int pid; int /*<<< orphan*/  fcs; int /*<<< orphan*/  ns_retries; TYPE_1__* port; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;
struct TYPE_2__ {int /*<<< orphan*/  fabric; } ;

/* Variables and functions */
#define  RPSM_EVENT_ADDRESS_CHANGE 137 
#define  RPSM_EVENT_DELETE 136 
#define  RPSM_EVENT_FAB_SCN 135 
#define  RPSM_EVENT_LOGO_IMP 134 
#define  RPSM_EVENT_LOGO_RCVD 133 
#define  RPSM_EVENT_PLOGI_COMP 132 
#define  RPSM_EVENT_PLOGI_RCVD 131 
#define  RPSM_EVENT_PRLO_RCVD 130 
#define  RPSM_EVENT_SCN_OFFLINE 129 
#define  RPSM_EVENT_SCN_ONLINE 128 
 int /*<<< orphan*/  bfa_fcs_fabric_is_switched (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_rport_hal_offline_action (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_adisc (struct bfa_fcs_rport_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_nsdisc (struct bfa_fcs_rport_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_adisc_online_sending ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logorcv ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logosend ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_nsquery_sending ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_online(struct bfa_fcs_rport_s *rport, enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_FAB_SCN:
		if (bfa_fcs_fabric_is_switched(rport->port->fabric)) {
			bfa_sm_set_state(rport,
					 bfa_fcs_rport_sm_nsquery_sending);
			rport->ns_retries = 0;
			bfa_fcs_rport_send_nsdisc(rport, NULL);
		} else {
			bfa_sm_set_state(rport,
				bfa_fcs_rport_sm_adisc_online_sending);
			bfa_fcs_rport_send_adisc(rport, NULL);
		}
		break;

	case RPSM_EVENT_PLOGI_RCVD:
	case RPSM_EVENT_LOGO_IMP:
	case RPSM_EVENT_ADDRESS_CHANGE:
	case RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcs_rport_hal_offline_action(rport);
		break;

	case RPSM_EVENT_SCN_ONLINE:
	case RPSM_EVENT_PLOGI_COMP:
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}