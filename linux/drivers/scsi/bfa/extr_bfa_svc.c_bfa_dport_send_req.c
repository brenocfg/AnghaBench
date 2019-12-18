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
struct bfi_diag_dport_req_s {int req; int /*<<< orphan*/  mh; void* payload; void* lpcnt; } ;
struct bfa_dport_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  payload; int /*<<< orphan*/  lpcnt; int /*<<< orphan*/  reqq_wait; } ;
typedef  enum bfi_dport_req { ____Placeholder_bfi_dport_req } bfi_dport_req ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_REQQ_DIAG ; 
 int /*<<< orphan*/  BFA_REQQ_PORT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_DIAG_H2I_DPORT ; 
 int BFI_DPORT_ENABLE ; 
 int BFI_DPORT_START ; 
 int /*<<< orphan*/  BFI_MC_DIAG ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_diag_dport_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_dport_send_req(struct bfa_dport_s *dport, enum bfi_dport_req req)
{
	struct bfi_diag_dport_req_s *m;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(dport->bfa, BFA_REQQ_DIAG);
	if (!m) {
		bfa_reqq_wait(dport->bfa, BFA_REQQ_PORT, &dport->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_DIAG, BFI_DIAG_H2I_DPORT,
		    bfa_fn_lpu(dport->bfa));
	m->req  = req;
	if ((req == BFI_DPORT_ENABLE) || (req == BFI_DPORT_START)) {
		m->lpcnt = cpu_to_be32(dport->lpcnt);
		m->payload = cpu_to_be32(dport->payload);
	}

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(dport->bfa, BFA_REQQ_DIAG, m->mh);

	return BFA_TRUE;
}