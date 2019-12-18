#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_s {int dummy; } ;
struct TYPE_5__ {int pwwn; } ;
struct TYPE_6__ {TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_3__* fcs; int /*<<< orphan*/  lps; TYPE_2__ bport; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;
struct TYPE_7__ {struct bfa_s* bfa; } ;

/* Variables and functions */
#define  BFA_FCS_FABRIC_SM_LINK_DOWN 130 
#define  BFA_FCS_FABRIC_SM_LINK_UP 129 
#define  BFA_FCS_FABRIC_SM_STOPCOMP 128 
 int /*<<< orphan*/  BFA_LPS_SM_LOGOUT ; 
 int /*<<< orphan*/  BFA_PORT_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  bfa_fcport_get_topology (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_cleanup ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_created ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_3__*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int) ; 

__attribute__((used)) static void
bfa_fcs_fabric_sm_stopping(struct bfa_fcs_fabric_s *fabric,
			   enum bfa_fcs_fabric_event event)
{
	struct bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_STOPCOMP:
		if (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP) {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		} else {
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
			bfa_sm_send_event(fabric->lps, BFA_LPS_SM_LOGOUT);
		}
		break;

	case BFA_FCS_FABRIC_SM_LINK_UP:
		break;

	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		if (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP)
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		else
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}