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
struct bfi_itn_create_req_s {int /*<<< orphan*/  mh; scalar_t__ msg_no; int /*<<< orphan*/  seq_rec; int /*<<< orphan*/  class; int /*<<< orphan*/  fw_handle; } ;
struct bfa_itnim_s {int /*<<< orphan*/  reqq; int /*<<< orphan*/  bfa; scalar_t__ msg_no; int /*<<< orphan*/  seq_rec; TYPE_1__* rport; int /*<<< orphan*/  reqq_wait; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  fw_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_ITN_H2I_CREATE_REQ ; 
 int /*<<< orphan*/  BFI_MC_ITN ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_itn_create_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_stats (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_create ; 

__attribute__((used)) static bfa_boolean_t
bfa_itnim_send_fwcreate(struct bfa_itnim_s *itnim)
{
	struct bfi_itn_create_req_s *m;

	itnim->msg_no++;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(itnim->bfa, itnim->reqq);
	if (!m) {
		bfa_reqq_wait(itnim->bfa, itnim->reqq, &itnim->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_ITN, BFI_ITN_H2I_CREATE_REQ,
			bfa_fn_lpu(itnim->bfa));
	m->fw_handle = itnim->rport->fw_handle;
	m->class = FC_CLASS_3;
	m->seq_rec = itnim->seq_rec;
	m->msg_no = itnim->msg_no;
	bfa_stats(itnim, fw_create);

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(itnim->bfa, itnim->reqq, m->mh);
	return BFA_TRUE;
}