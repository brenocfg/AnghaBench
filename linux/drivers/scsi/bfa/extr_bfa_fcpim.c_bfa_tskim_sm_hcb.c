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
struct bfa_tskim_s {int tsk_tag; int /*<<< orphan*/  bfa; } ;
typedef  enum bfa_tskim_event { ____Placeholder_bfa_tskim_event } bfa_tskim_event ;

/* Variables and functions */
#define  BFA_TSKIM_SM_CLEANUP 130 
#define  BFA_TSKIM_SM_HCB 129 
#define  BFA_TSKIM_SM_HWFAIL 128 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_tskim_free (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_notify_comp (struct bfa_tskim_s*) ; 
 int /*<<< orphan*/  bfa_tskim_sm_uninit ; 

__attribute__((used)) static void
bfa_tskim_sm_hcb(struct bfa_tskim_s *tskim, enum bfa_tskim_event event)
{
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	switch (event) {
	case BFA_TSKIM_SM_HCB:
		bfa_sm_set_state(tskim, bfa_tskim_sm_uninit);
		bfa_tskim_free(tskim);
		break;

	case BFA_TSKIM_SM_CLEANUP:
		bfa_tskim_notify_comp(tskim);
		break;

	case BFA_TSKIM_SM_HWFAIL:
		break;

	default:
		bfa_sm_fault(tskim->bfa, event);
	}
}