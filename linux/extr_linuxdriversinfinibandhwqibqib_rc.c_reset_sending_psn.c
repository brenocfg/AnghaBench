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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ opcode; } ;
struct rvt_swqe {scalar_t__ lpsn; TYPE_1__ wr; } ;
struct rvt_qp {scalar_t__ s_last; scalar_t__ s_size; scalar_t__ s_tail; scalar_t__ s_sending_psn; } ;

/* Variables and functions */
 scalar_t__ IB_WR_RDMA_READ ; 
 scalar_t__ qib_cmp24 (scalar_t__,scalar_t__) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 

__attribute__((used)) static void reset_sending_psn(struct rvt_qp *qp, u32 psn)
{
	struct rvt_swqe *wqe;
	u32 n = qp->s_last;

	/* Find the work request corresponding to the given PSN. */
	for (;;) {
		wqe = rvt_get_swqe_ptr(qp, n);
		if (qib_cmp24(psn, wqe->lpsn) <= 0) {
			if (wqe->wr.opcode == IB_WR_RDMA_READ)
				qp->s_sending_psn = wqe->lpsn + 1;
			else
				qp->s_sending_psn = psn + 1;
			break;
		}
		if (++n == qp->s_size)
			n = 0;
		if (n == qp->s_tail)
			break;
	}
}