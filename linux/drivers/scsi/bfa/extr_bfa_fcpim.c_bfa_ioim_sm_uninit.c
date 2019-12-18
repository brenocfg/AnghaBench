#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioim_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  hcb_qe; TYPE_2__* itnim; int /*<<< orphan*/  nsges; int /*<<< orphan*/  qe; TYPE_1__* fcpim; } ;
typedef  enum bfa_ioim_event { ____Placeholder_bfa_ioim_event } bfa_ioim_event ;
struct TYPE_5__ {int /*<<< orphan*/  pending_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioim_comp_q; } ;

/* Variables and functions */
#define  BFA_IOIM_SM_ABORT 130 
#define  BFA_IOIM_SM_IOTOV 129 
#define  BFA_IOIM_SM_START 128 
 int /*<<< orphan*/  BFI_SGE_INLINE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __bfa_cb_ioim_abort ; 
 int /*<<< orphan*/  __bfa_cb_ioim_pathtov ; 
 int /*<<< orphan*/  bfa_cb_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_move_to_comp_q (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_send_ioreq (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_sgpg_alloc (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_ioim_sm_active ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb ; 
 int /*<<< orphan*/  bfa_ioim_sm_qfull ; 
 int /*<<< orphan*/  bfa_ioim_sm_sgalloc ; 
 int /*<<< orphan*/  bfa_itnim_hold_io (TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_itnim_is_online (TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_ioim_sm_uninit(struct bfa_ioim_s *ioim, enum bfa_ioim_event event)
{
	switch (event) {
	case BFA_IOIM_SM_START:
		if (!bfa_itnim_is_online(ioim->itnim)) {
			if (!bfa_itnim_hold_io(ioim->itnim)) {
				bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
				list_del(&ioim->qe);
				list_add_tail(&ioim->qe,
					&ioim->fcpim->ioim_comp_q);
				bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
						__bfa_cb_ioim_pathtov, ioim);
			} else {
				list_del(&ioim->qe);
				list_add_tail(&ioim->qe,
					&ioim->itnim->pending_q);
			}
			break;
		}

		if (ioim->nsges > BFI_SGE_INLINE) {
			if (!bfa_ioim_sgpg_alloc(ioim)) {
				bfa_sm_set_state(ioim, bfa_ioim_sm_sgalloc);
				return;
			}
		}

		if (!bfa_ioim_send_ioreq(ioim)) {
			bfa_sm_set_state(ioim, bfa_ioim_sm_qfull);
			break;
		}

		bfa_sm_set_state(ioim, bfa_ioim_sm_active);
		break;

	case BFA_IOIM_SM_IOTOV:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
				__bfa_cb_ioim_pathtov, ioim);
		break;

	case BFA_IOIM_SM_ABORT:
		/*
		 * IO in pending queue can get abort requests. Complete abort
		 * requests immediately.
		 */
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		WARN_ON(!bfa_q_is_on_q(&ioim->itnim->pending_q, ioim));
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
			__bfa_cb_ioim_abort, ioim);
		break;

	default:
		bfa_sm_fault(ioim->bfa, event);
	}
}