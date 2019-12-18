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
struct TYPE_3__ {int pwwn; } ;
struct TYPE_4__ {TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  fcs; TYPE_2__ bport; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;

/* Variables and functions */
#define  BFA_FCS_FABRIC_SM_CONT_OP 129 
#define  BFA_FCS_FABRIC_SM_ISOLATE 128 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_evfp_done ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_isolated ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_fabric_sm_evfp(struct bfa_fcs_fabric_s *fabric,
		       enum bfa_fcs_fabric_event event)
{
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_CONT_OP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_evfp_done);
		break;

	case BFA_FCS_FABRIC_SM_ISOLATE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_isolated);
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}