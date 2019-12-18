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
struct bfi_tskim_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  tm_flags; int /*<<< orphan*/  lun; int /*<<< orphan*/  t_secs; int /*<<< orphan*/  itn_fhdl; int /*<<< orphan*/  tsk_tag; } ;
struct bfa_tskim_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  tm_cmnd; int /*<<< orphan*/  lun; int /*<<< orphan*/  tsecs; struct bfa_itnim_s* itnim; int /*<<< orphan*/  tsk_tag; } ;
struct bfa_itnim_s {int /*<<< orphan*/  reqq; TYPE_1__* rport; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  fw_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_MC_TSKIM ; 
 int /*<<< orphan*/  BFI_TSKIM_H2I_TM_REQ ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_tskim_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_tskim_send(struct bfa_tskim_s *tskim)
{
	struct bfa_itnim_s *itnim = tskim->itnim;
	struct bfi_tskim_req_s *m;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(tskim->bfa, itnim->reqq);
	if (!m)
		return BFA_FALSE;

	/*
	 * build i/o request message next
	 */
	bfi_h2i_set(m->mh, BFI_MC_TSKIM, BFI_TSKIM_H2I_TM_REQ,
			bfa_fn_lpu(tskim->bfa));

	m->tsk_tag = cpu_to_be16(tskim->tsk_tag);
	m->itn_fhdl = tskim->itnim->rport->fw_handle;
	m->t_secs = tskim->tsecs;
	m->lun = tskim->lun;
	m->tm_flags = tskim->tm_cmnd;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(tskim->bfa, itnim->reqq, m->mh);
	return BFA_TRUE;
}