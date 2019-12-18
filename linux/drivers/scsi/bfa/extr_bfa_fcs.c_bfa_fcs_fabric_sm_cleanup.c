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
struct TYPE_5__ {int pwwn; } ;
struct TYPE_6__ {TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_3__* fcs; TYPE_2__ bport; } ;
typedef  enum bfa_fcs_fabric_event { ____Placeholder_bfa_fcs_fabric_event } bfa_fcs_fabric_event ;
struct TYPE_7__ {int /*<<< orphan*/  wc; } ;

/* Variables and functions */
#define  BFA_FCS_FABRIC_SM_LINK_DOWN 130 
#define  BFA_FCS_FABRIC_SM_LOGOCOMP 129 
#define  BFA_FCS_FABRIC_SM_STOPCOMP 128 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_created ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_3__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_fcs_fabric_sm_cleanup(struct bfa_fcs_fabric_s *fabric,
			  enum bfa_fcs_fabric_event event)
{
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	switch (event) {
	case BFA_FCS_FABRIC_SM_STOPCOMP:
	case BFA_FCS_FABRIC_SM_LOGOCOMP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		bfa_wc_down(&(fabric->fcs)->wc);
		break;

	case BFA_FCS_FABRIC_SM_LINK_DOWN:
		/*
		 * Ignore - can get this event if we get notified about IOC down
		 * before the fabric completion callbk is done.
		 */
		break;

	default:
		bfa_sm_fault(fabric->fcs, event);
	}
}