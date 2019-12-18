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
struct siw_rqe {int /*<<< orphan*/  flags; } ;
struct siw_wqe {scalar_t__ wr_status; int /*<<< orphan*/  sqe; int /*<<< orphan*/  bytes; struct siw_rqe rqe; } ;
struct TYPE_6__ {int rq_size; } ;
struct TYPE_5__ {struct siw_wqe wqe_active; } ;
struct TYPE_4__ {struct siw_wqe wqe_active; } ;
struct siw_qp {size_t rq_get; TYPE_3__ attrs; struct siw_rqe* recvq; TYPE_2__ rx_tagged; TYPE_1__ rx_untagged; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ SIW_OP_READ ; 
 scalar_t__ SIW_OP_READ_RESPONSE ; 
 scalar_t__ SIW_OP_RECEIVE ; 
 scalar_t__ SIW_OP_WRITE ; 
 int /*<<< orphan*/  SIW_WC_WR_FLUSH_ERR ; 
 scalar_t__ SIW_WR_IDLE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rx_type (struct siw_wqe*) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ siw_rqe_complete (struct siw_qp*,struct siw_rqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_sqe_complete (struct siw_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_wqe_put_mem (struct siw_wqe*,scalar_t__) ; 

void siw_rq_flush(struct siw_qp *qp)
{
	struct siw_wqe *wqe = &qp->rx_untagged.wqe_active;

	/*
	 * Flush an in-progress untagged operation if present
	 */
	if (wqe->wr_status != SIW_WR_IDLE) {
		siw_dbg_qp(qp, "flush current rqe, type %d, status %d\n",
			   rx_type(wqe), wqe->wr_status);

		siw_wqe_put_mem(wqe, rx_type(wqe));

		if (rx_type(wqe) == SIW_OP_RECEIVE) {
			siw_rqe_complete(qp, &wqe->rqe, wqe->bytes,
					 0, SIW_WC_WR_FLUSH_ERR);
		} else if (rx_type(wqe) != SIW_OP_READ &&
			   rx_type(wqe) != SIW_OP_READ_RESPONSE &&
			   rx_type(wqe) != SIW_OP_WRITE) {
			siw_sqe_complete(qp, &wqe->sqe, 0, SIW_WC_WR_FLUSH_ERR);
		}
		wqe->wr_status = SIW_WR_IDLE;
	}
	wqe = &qp->rx_tagged.wqe_active;

	if (wqe->wr_status != SIW_WR_IDLE) {
		siw_wqe_put_mem(wqe, rx_type(wqe));
		wqe->wr_status = SIW_WR_IDLE;
	}
	/*
	 * Flush the Receive Queue
	 */
	while (qp->attrs.rq_size) {
		struct siw_rqe *rqe =
			&qp->recvq[qp->rq_get % qp->attrs.rq_size];

		if (!READ_ONCE(rqe->flags))
			break;

		if (siw_rqe_complete(qp, rqe, 0, 0, SIW_WC_WR_FLUSH_ERR) != 0)
			break;

		WRITE_ONCE(rqe->flags, 0);
		qp->rq_get++;
	}
}