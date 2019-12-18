#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int resid; int sge_offset; } ;
struct TYPE_5__ {int send_flags; int /*<<< orphan*/  opcode; } ;
struct rxe_send_wqe {int iova; TYPE_3__ dma; TYPE_2__ wr; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
struct rxe_qp {int mtu; TYPE_1__ req; } ;

/* Variables and functions */
 int IB_SEND_INLINE ; 
 unsigned int WR_WRITE_MASK ; 
 int /*<<< orphan*/  advance_dma_data (TYPE_3__*,int) ; 
 int /*<<< orphan*/  next_opcode (struct rxe_qp*,struct rxe_send_wqe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void retry_first_write_send(struct rxe_qp *qp,
					  struct rxe_send_wqe *wqe,
					  unsigned int mask, int npsn)
{
	int i;

	for (i = 0; i < npsn; i++) {
		int to_send = (wqe->dma.resid > qp->mtu) ?
				qp->mtu : wqe->dma.resid;

		qp->req.opcode = next_opcode(qp, wqe,
					     wqe->wr.opcode);

		if (wqe->wr.send_flags & IB_SEND_INLINE) {
			wqe->dma.resid -= to_send;
			wqe->dma.sge_offset += to_send;
		} else {
			advance_dma_data(&wqe->dma, to_send);
		}
		if (mask & WR_WRITE_MASK)
			wqe->iova += qp->mtu;
	}
}