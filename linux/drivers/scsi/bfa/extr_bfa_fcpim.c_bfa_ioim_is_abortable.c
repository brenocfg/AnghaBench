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
struct bfa_ioim_s {TYPE_1__* itnim; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  bfa_ioim_sm_abort ; 
 int /*<<< orphan*/  bfa_ioim_sm_abort_qfull ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb ; 
 int /*<<< orphan*/  bfa_ioim_sm_hcb_free ; 
 int /*<<< orphan*/  bfa_ioim_sm_resfree ; 
 int /*<<< orphan*/  bfa_ioim_sm_uninit ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_ioim_s*) ; 
 scalar_t__ bfa_sm_cmp_state (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioim_is_abortable(struct bfa_ioim_s *ioim)
{
	if ((bfa_sm_cmp_state(ioim, bfa_ioim_sm_uninit) &&
	    (!bfa_q_is_on_q(&ioim->itnim->pending_q, ioim)))	||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_abort))		||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_abort_qfull))	||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_hcb))		||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_hcb_free))	||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_resfree)))
		return BFA_FALSE;

	return BFA_TRUE;
}