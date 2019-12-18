#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_s {int dummy; } ;
struct TYPE_5__ {int pwwn; } ;
struct TYPE_7__ {TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_2__* fcs; int /*<<< orphan*/  lps; TYPE_4__ bport; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;
struct TYPE_6__ {struct bfa_s* bfa; } ;

/* Variables and functions */
#define  BFA_FCS_FABRIC_SM_AUTH_FAILED 132 
#define  BFA_FCS_FABRIC_SM_AUTH_SUCCESS 131 
#define  BFA_FCS_FABRIC_SM_DELETE 130 
#define  BFA_FCS_FABRIC_SM_LINK_DOWN 129 
#define  BFA_FCS_FABRIC_SM_STOP 128 
 int /*<<< orphan*/  BFA_LPS_SM_OFFLINE ; 
 int /*<<< orphan*/  BFA_PORT_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  bfa_fcport_get_topology (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_delete (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_notify_offline (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_auth_failed ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_deleting ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_linkdown ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_stopping ; 
 int /*<<< orphan*/  bfa_fcs_fabric_stop (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_offline (TYPE_4__*) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int) ; 

void
bfa_fcs_fabric_sm_online(struct bfa_fcs_fabric_s *fabric,
			 enum bfa_fcs_fabric_event event)
{
	struct bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkdown);
		if (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP) {
			bfa_fcs_lport_offline(&fabric->bport);
		} else {
			bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
			bfa_fcs_fabric_notify_offline(fabric);
		}
		break;

	case BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		break;

	case BFA_FCS_FABRIC_SM_STOP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_stopping);
		bfa_fcs_fabric_stop(fabric);
		break;

	case BFA_FCS_FABRIC_SM_AUTH_FAILED:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_auth_failed);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		break;

	case BFA_FCS_FABRIC_SM_AUTH_SUCCESS:
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}