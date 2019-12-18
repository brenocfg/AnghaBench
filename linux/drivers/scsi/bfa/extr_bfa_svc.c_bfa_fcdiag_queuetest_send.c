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
typedef  size_t u32 ;
struct bfi_diag_qtest_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct bfa_fcdiag_s {TYPE_1__ qtest; int /*<<< orphan*/  bfa; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_DEVBUSY ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFI_DIAG_H2I_QTEST ; 
 size_t BFI_LMSG_PL_WSZ ; 
 int /*<<< orphan*/  BFI_MC_DIAG ; 
 int /*<<< orphan*/  QTEST_PAT_DEFAULT ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_diag_qtest_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcdiag_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_status_t
bfa_fcdiag_queuetest_send(struct bfa_fcdiag_s *fcdiag)
{
	u32	i;
	struct bfi_diag_qtest_req_s *req;

	req = bfa_reqq_next(fcdiag->bfa, fcdiag->qtest.queue);
	if (!req)
		return BFA_STATUS_DEVBUSY;

	/* build host command */
	bfi_h2i_set(req->mh, BFI_MC_DIAG, BFI_DIAG_H2I_QTEST,
		bfa_fn_lpu(fcdiag->bfa));

	for (i = 0; i < BFI_LMSG_PL_WSZ; i++)
		req->data[i] = QTEST_PAT_DEFAULT;

	bfa_trc(fcdiag, fcdiag->qtest.queue);
	/* ring door bell */
	bfa_reqq_produce(fcdiag->bfa, fcdiag->qtest.queue, req->mh);
	return BFA_STATUS_OK;
}