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
struct ocrdma_qp {int dummy; } ;
struct ocrdma_cqe {int /*<<< orphan*/  flags_status_srcqpn; } ;
struct ib_wc {int dummy; } ;

/* Variables and functions */
 int OCRDMA_CQE_STATUS_MASK ; 
 int OCRDMA_CQE_STATUS_SHIFT ; 
 int OCRDMA_CQE_SUCCESS ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ocrdma_poll_err_scqe (struct ocrdma_qp*,struct ocrdma_cqe*,struct ib_wc*,int*,int*) ; 
 int ocrdma_poll_success_scqe (struct ocrdma_qp*,struct ocrdma_cqe*,struct ib_wc*,int*) ; 

__attribute__((used)) static bool ocrdma_poll_scqe(struct ocrdma_qp *qp, struct ocrdma_cqe *cqe,
			     struct ib_wc *ibwc, bool *polled, bool *stop)
{
	int status;
	bool expand;

	status = (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_STATUS_MASK) >> OCRDMA_CQE_STATUS_SHIFT;

	if (status == OCRDMA_CQE_SUCCESS)
		expand = ocrdma_poll_success_scqe(qp, cqe, ibwc, polled);
	else
		expand = ocrdma_poll_err_scqe(qp, cqe, ibwc, polled, stop);
	return expand;
}