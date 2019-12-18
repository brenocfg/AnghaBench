#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int resid; int length; scalar_t__ sge_offset; scalar_t__ cur_sge; } ;
struct TYPE_12__ {int remote_addr; } ;
struct TYPE_11__ {int remote_addr; } ;
struct TYPE_13__ {TYPE_4__ rdma; TYPE_3__ atomic; } ;
struct TYPE_14__ {TYPE_5__ wr; int /*<<< orphan*/  opcode; } ;
struct rxe_send_wqe {scalar_t__ state; int iova; int first_psn; TYPE_8__ dma; TYPE_6__ wr; } ;
struct TYPE_15__ {int psn; } ;
struct TYPE_10__ {int /*<<< orphan*/  queue; } ;
struct TYPE_9__ {int psn; int opcode; void* wqe_index; } ;
struct rxe_qp {int mtu; TYPE_7__ comp; TYPE_2__ sq; TYPE_1__ req; } ;

/* Variables and functions */
 int BTH_PSN_MASK ; 
 unsigned int WR_ATOMIC_MASK ; 
 unsigned int WR_READ_MASK ; 
 unsigned int WR_READ_OR_WRITE_MASK ; 
 unsigned int WR_WRITE_OR_SEND_MASK ; 
 struct rxe_send_wqe* addr_from_index (int /*<<< orphan*/ ,unsigned int) ; 
 void* consumer_index (int /*<<< orphan*/ ) ; 
 unsigned int next_index (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int producer_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retry_first_write_send (struct rxe_qp*,struct rxe_send_wqe*,unsigned int,int) ; 
 scalar_t__ wqe_state_done ; 
 scalar_t__ wqe_state_posted ; 
 unsigned int wr_opcode_mask (int /*<<< orphan*/ ,struct rxe_qp*) ; 

__attribute__((used)) static void req_retry(struct rxe_qp *qp)
{
	struct rxe_send_wqe *wqe;
	unsigned int wqe_index;
	unsigned int mask;
	int npsn;
	int first = 1;

	qp->req.wqe_index	= consumer_index(qp->sq.queue);
	qp->req.psn		= qp->comp.psn;
	qp->req.opcode		= -1;

	for (wqe_index = consumer_index(qp->sq.queue);
		wqe_index != producer_index(qp->sq.queue);
		wqe_index = next_index(qp->sq.queue, wqe_index)) {
		wqe = addr_from_index(qp->sq.queue, wqe_index);
		mask = wr_opcode_mask(wqe->wr.opcode, qp);

		if (wqe->state == wqe_state_posted)
			break;

		if (wqe->state == wqe_state_done)
			continue;

		wqe->iova = (mask & WR_ATOMIC_MASK) ?
			     wqe->wr.wr.atomic.remote_addr :
			     (mask & WR_READ_OR_WRITE_MASK) ?
			     wqe->wr.wr.rdma.remote_addr :
			     0;

		if (!first || (mask & WR_READ_MASK) == 0) {
			wqe->dma.resid = wqe->dma.length;
			wqe->dma.cur_sge = 0;
			wqe->dma.sge_offset = 0;
		}

		if (first) {
			first = 0;

			if (mask & WR_WRITE_OR_SEND_MASK) {
				npsn = (qp->comp.psn - wqe->first_psn) &
					BTH_PSN_MASK;
				retry_first_write_send(qp, wqe, mask, npsn);
			}

			if (mask & WR_READ_MASK) {
				npsn = (wqe->dma.length - wqe->dma.resid) /
					qp->mtu;
				wqe->iova += npsn * qp->mtu;
			}
		}

		wqe->state = wqe_state_posted;
	}
}