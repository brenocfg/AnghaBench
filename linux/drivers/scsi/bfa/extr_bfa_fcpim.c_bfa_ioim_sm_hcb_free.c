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
struct bfa_ioim_s {int iotag; int /*<<< orphan*/  bfa; TYPE_1__* fcpim; int /*<<< orphan*/  qe; } ;
typedef  enum bfa_ioim_event { ____Placeholder_bfa_ioim_event } bfa_ioim_event ;
struct TYPE_2__ {int /*<<< orphan*/  ioim_resfree_q; } ;

/* Variables and functions */
#define  BFA_IOIM_SM_CLEANUP 131 
#define  BFA_IOIM_SM_FREE 130 
#define  BFA_IOIM_SM_HCB 129 
#define  BFA_IOIM_SM_HWFAIL 128 
 int /*<<< orphan*/  bfa_ioim_notify_cleanup (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb ; 
 int /*<<< orphan*/  bfa_ioim_sm_resfree ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_ioim_sm_hcb_free(struct bfa_ioim_s *ioim, enum bfa_ioim_event event)
{
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	switch (event) {
	case BFA_IOIM_SM_HCB:
		bfa_sm_set_state(ioim, bfa_ioim_sm_resfree);
		list_del(&ioim->qe);
		list_add_tail(&ioim->qe, &ioim->fcpim->ioim_resfree_q);
		break;

	case BFA_IOIM_SM_FREE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		break;

	case BFA_IOIM_SM_CLEANUP:
		bfa_ioim_notify_cleanup(ioim);
		break;

	case BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		break;

	default:
		bfa_sm_fault(ioim->bfa, event);
	}
}