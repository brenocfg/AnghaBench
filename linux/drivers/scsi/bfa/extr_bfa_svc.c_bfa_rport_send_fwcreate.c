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
typedef  int /*<<< orphan*/  u8 ;
struct bfi_rport_create_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  cisc; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  vf_en; int /*<<< orphan*/  fc_class; int /*<<< orphan*/  local_pid; int /*<<< orphan*/  lp_fwtag; int /*<<< orphan*/  pid; int /*<<< orphan*/  max_frmsz; int /*<<< orphan*/  bfa_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cisc; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  vf_en; int /*<<< orphan*/  fc_class; int /*<<< orphan*/  local_pid; scalar_t__ lp_tag; int /*<<< orphan*/  pid; int /*<<< orphan*/  max_frmsz; } ;
struct bfa_rport_s {int /*<<< orphan*/  bfa; TYPE_1__ rport_info; int /*<<< orphan*/  rport_tag; int /*<<< orphan*/  reqq_wait; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_REQQ_RPORT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_MC_RPORT ; 
 int /*<<< orphan*/  BFI_RPORT_H2I_CREATE_REQ ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_lps_get_fwtag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bfi_rport_create_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_rport_send_fwcreate(struct bfa_rport_s *rp)
{
	struct bfi_rport_create_req_s *m;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(rp->bfa, BFA_REQQ_RPORT);
	if (!m) {
		bfa_reqq_wait(rp->bfa, BFA_REQQ_RPORT, &rp->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_RPORT, BFI_RPORT_H2I_CREATE_REQ,
			bfa_fn_lpu(rp->bfa));
	m->bfa_handle = rp->rport_tag;
	m->max_frmsz = cpu_to_be16(rp->rport_info.max_frmsz);
	m->pid = rp->rport_info.pid;
	m->lp_fwtag = bfa_lps_get_fwtag(rp->bfa, (u8)rp->rport_info.lp_tag);
	m->local_pid = rp->rport_info.local_pid;
	m->fc_class = rp->rport_info.fc_class;
	m->vf_en = rp->rport_info.vf_en;
	m->vf_id = rp->rport_info.vf_id;
	m->cisc = rp->rport_info.cisc;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(rp->bfa, BFA_REQQ_RPORT, m->mh);
	return BFA_TRUE;
}