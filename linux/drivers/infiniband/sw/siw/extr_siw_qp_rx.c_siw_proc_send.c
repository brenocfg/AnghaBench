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
typedef  int u32 ;
struct TYPE_4__ {struct siw_sge* sge; } ;
struct siw_wqe {int /*<<< orphan*/  processed; struct siw_mem** mem; TYPE_1__ rqe; } ;
struct siw_sge {scalar_t__ length; scalar_t__ laddr; } ;
struct siw_rx_stream {scalar_t__ state; int fpdu_part_rem; scalar_t__ skb_new; int fpdu_part_rcvd; } ;
struct siw_rx_fpdu {size_t sge_idx; scalar_t__ sge_off; scalar_t__ pbl_idx; scalar_t__ first_ddp_seg; } ;
struct siw_qp {TYPE_3__* srq; struct ib_pd* pd; struct siw_rx_fpdu rx_untagged; struct siw_rx_stream rx_stream; } ;
struct siw_mem {int /*<<< orphan*/  umem; int /*<<< orphan*/  is_pbl; int /*<<< orphan*/ * mem_obj; } ;
struct ib_pd {int dummy; } ;
struct TYPE_5__ {struct ib_pd* pd; } ;
struct TYPE_6__ {TYPE_2__ base_srq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDP_ECODE_CATASTROPHIC ; 
 int /*<<< orphan*/  DDP_ECODE_UT_INVALID_MSN_NOBUF ; 
 int /*<<< orphan*/  DDP_ETYPE_CATASTROPHIC ; 
 int /*<<< orphan*/  DDP_ETYPE_UNTAGGED_BUF ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_EVENT_QP_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 scalar_t__ SIW_GET_DATA_START ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_DDP ; 
 int min (int,scalar_t__) ; 
 struct siw_wqe* rx_wqe (struct siw_rx_fpdu*) ; 
 int siw_check_sge (struct ib_pd*,struct siw_sge*,struct siw_mem**,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  siw_init_terminate (struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_qp_event (struct siw_qp*,int /*<<< orphan*/ ) ; 
 struct siw_wqe* siw_rqe_get (struct siw_qp*) ; 
 int siw_rx_kva (struct siw_rx_stream*,void*,int) ; 
 int siw_rx_pbl (struct siw_rx_stream*,scalar_t__*,struct siw_mem*,scalar_t__,int) ; 
 int siw_rx_umem (struct siw_rx_stream*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int siw_send_check_ntoh (struct siw_rx_stream*,struct siw_rx_fpdu*) ; 
 scalar_t__ unlikely (int) ; 

int siw_proc_send(struct siw_qp *qp)
{
	struct siw_rx_stream *srx = &qp->rx_stream;
	struct siw_rx_fpdu *frx = &qp->rx_untagged;
	struct siw_wqe *wqe;
	u32 data_bytes; /* all data bytes available */
	u32 rcvd_bytes; /* sum of data bytes rcvd */
	int rv = 0;

	if (frx->first_ddp_seg) {
		wqe = siw_rqe_get(qp);
		if (unlikely(!wqe)) {
			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_UNTAGGED_BUF,
					   DDP_ECODE_UT_INVALID_MSN_NOBUF, 0);
			return -ENOENT;
		}
	} else {
		wqe = rx_wqe(frx);
	}
	if (srx->state == SIW_GET_DATA_START) {
		rv = siw_send_check_ntoh(srx, frx);
		if (unlikely(rv)) {
			siw_qp_event(qp, IB_EVENT_QP_FATAL);
			return rv;
		}
		if (!srx->fpdu_part_rem) /* zero length SEND */
			return 0;
	}
	data_bytes = min(srx->fpdu_part_rem, srx->skb_new);
	rcvd_bytes = 0;

	/* A zero length SEND will skip below loop */
	while (data_bytes) {
		struct ib_pd *pd;
		struct siw_mem **mem, *mem_p;
		struct siw_sge *sge;
		u32 sge_bytes; /* data bytes avail for SGE */

		sge = &wqe->rqe.sge[frx->sge_idx];

		if (!sge->length) {
			/* just skip empty sge's */
			frx->sge_idx++;
			frx->sge_off = 0;
			frx->pbl_idx = 0;
			continue;
		}
		sge_bytes = min(data_bytes, sge->length - frx->sge_off);
		mem = &wqe->mem[frx->sge_idx];

		/*
		 * check with QP's PD if no SRQ present, SRQ's PD otherwise
		 */
		pd = qp->srq == NULL ? qp->pd : qp->srq->base_srq.pd;

		rv = siw_check_sge(pd, sge, mem, IB_ACCESS_LOCAL_WRITE,
				   frx->sge_off, sge_bytes);
		if (unlikely(rv)) {
			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_CATASTROPHIC,
					   DDP_ECODE_CATASTROPHIC, 0);

			siw_qp_event(qp, IB_EVENT_QP_ACCESS_ERR);
			break;
		}
		mem_p = *mem;
		if (mem_p->mem_obj == NULL)
			rv = siw_rx_kva(srx,
				(void *)(uintptr_t)(sge->laddr + frx->sge_off),
				sge_bytes);
		else if (!mem_p->is_pbl)
			rv = siw_rx_umem(srx, mem_p->umem,
					 sge->laddr + frx->sge_off, sge_bytes);
		else
			rv = siw_rx_pbl(srx, &frx->pbl_idx, mem_p,
					sge->laddr + frx->sge_off, sge_bytes);

		if (unlikely(rv != sge_bytes)) {
			wqe->processed += rcvd_bytes;

			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_CATASTROPHIC,
					   DDP_ECODE_CATASTROPHIC, 0);
			return -EINVAL;
		}
		frx->sge_off += rv;

		if (frx->sge_off == sge->length) {
			frx->sge_idx++;
			frx->sge_off = 0;
			frx->pbl_idx = 0;
		}
		data_bytes -= rv;
		rcvd_bytes += rv;

		srx->fpdu_part_rem -= rv;
		srx->fpdu_part_rcvd += rv;
	}
	wqe->processed += rcvd_bytes;

	if (!srx->fpdu_part_rem)
		return 0;

	return (rv < 0) ? rv : -EAGAIN;
}