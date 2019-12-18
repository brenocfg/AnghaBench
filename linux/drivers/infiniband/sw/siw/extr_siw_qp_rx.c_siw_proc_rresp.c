#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct siw_sge* sge; int /*<<< orphan*/  opcode; } ;
struct siw_wqe {int wr_status; scalar_t__ processed; int /*<<< orphan*/  wc_status; int /*<<< orphan*/  bytes; struct siw_mem** mem; TYPE_2__ sqe; } ;
struct siw_sge {scalar_t__ laddr; } ;
struct siw_rx_stream {scalar_t__ fpdu_part_rcvd; int /*<<< orphan*/  ddp_to; scalar_t__ fpdu_part_rem; int /*<<< orphan*/  skb_new; } ;
struct siw_rx_fpdu {int /*<<< orphan*/  pbl_idx; scalar_t__ first_ddp_seg; } ;
struct TYPE_3__ {int orq_size; } ;
struct siw_qp {int orq_get; int /*<<< orphan*/  pd; TYPE_1__ attrs; struct siw_rx_fpdu rx_tagged; struct siw_rx_stream rx_stream; } ;
struct siw_mem {int /*<<< orphan*/  umem; int /*<<< orphan*/  is_pbl; int /*<<< orphan*/ * mem_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDP_ECODE_CATASTROPHIC ; 
 int /*<<< orphan*/  DDP_ETYPE_CATASTROPHIC ; 
 int /*<<< orphan*/  DDP_ETYPE_TAGGED_BUF ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_EVENT_QP_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  SIW_WC_GENERAL_ERR ; 
 int /*<<< orphan*/  SIW_WC_LOC_PROT_ERR ; 
 int SIW_WR_IDLE ; 
 int SIW_WR_INPROGRESS ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_DDP ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  qp_id (struct siw_qp*) ; 
 struct siw_wqe* rx_wqe (struct siw_rx_fpdu*) ; 
 int siw_check_sge (int /*<<< orphan*/ ,struct siw_sge*,struct siw_mem**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,int) ; 
 int /*<<< orphan*/  siw_init_terminate (struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int siw_orqe_start_rx (struct siw_qp*) ; 
 int /*<<< orphan*/  siw_qp_event (struct siw_qp*,int /*<<< orphan*/ ) ; 
 int siw_rresp_check_ntoh (struct siw_rx_stream*,struct siw_rx_fpdu*) ; 
 int siw_rx_kva (struct siw_rx_stream*,void*,int) ; 
 int siw_rx_pbl (struct siw_rx_stream*,int /*<<< orphan*/ *,struct siw_mem*,scalar_t__,int) ; 
 int siw_rx_umem (struct siw_rx_stream*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  siw_tagged_error (int) ; 
 scalar_t__ unlikely (int) ; 

int siw_proc_rresp(struct siw_qp *qp)
{
	struct siw_rx_stream *srx = &qp->rx_stream;
	struct siw_rx_fpdu *frx = &qp->rx_tagged;
	struct siw_wqe *wqe = rx_wqe(frx);
	struct siw_mem **mem, *mem_p;
	struct siw_sge *sge;
	int bytes, rv;

	if (frx->first_ddp_seg) {
		if (unlikely(wqe->wr_status != SIW_WR_IDLE)) {
			pr_warn("siw: [QP %u]: proc RRESP: status %d, op %d\n",
				qp_id(qp), wqe->wr_status, wqe->sqe.opcode);
			rv = -EPROTO;
			goto error_term;
		}
		/*
		 * fetch pending RREQ from orq
		 */
		rv = siw_orqe_start_rx(qp);
		if (rv) {
			pr_warn("siw: [QP %u]: ORQ empty at idx %d\n",
				qp_id(qp), qp->orq_get % qp->attrs.orq_size);
			goto error_term;
		}
		rv = siw_rresp_check_ntoh(srx, frx);
		if (unlikely(rv)) {
			siw_qp_event(qp, IB_EVENT_QP_FATAL);
			return rv;
		}
	} else {
		if (unlikely(wqe->wr_status != SIW_WR_INPROGRESS)) {
			pr_warn("siw: [QP %u]: resume RRESP: status %d\n",
				qp_id(qp), wqe->wr_status);
			rv = -EPROTO;
			goto error_term;
		}
	}
	if (!srx->fpdu_part_rem) /* zero length RRESPONSE */
		return 0;

	sge = wqe->sqe.sge; /* there is only one */
	mem = &wqe->mem[0];

	if (!(*mem)) {
		/*
		 * check target memory which resolves memory on first fragment
		 */
		rv = siw_check_sge(qp->pd, sge, mem, IB_ACCESS_LOCAL_WRITE, 0,
				   wqe->bytes);
		if (unlikely(rv)) {
			siw_dbg_qp(qp, "target mem check: %d\n", rv);
			wqe->wc_status = SIW_WC_LOC_PROT_ERR;

			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_TAGGED_BUF,
					   siw_tagged_error(-rv), 0);

			siw_qp_event(qp, IB_EVENT_QP_ACCESS_ERR);

			return -EINVAL;
		}
	}
	mem_p = *mem;

	bytes = min(srx->fpdu_part_rem, srx->skb_new);

	if (mem_p->mem_obj == NULL)
		rv = siw_rx_kva(srx,
			(void *)(uintptr_t)(sge->laddr + wqe->processed),
			bytes);
	else if (!mem_p->is_pbl)
		rv = siw_rx_umem(srx, mem_p->umem, sge->laddr + wqe->processed,
				 bytes);
	else
		rv = siw_rx_pbl(srx, &frx->pbl_idx, mem_p,
				sge->laddr + wqe->processed, bytes);
	if (rv != bytes) {
		wqe->wc_status = SIW_WC_GENERAL_ERR;
		rv = -EINVAL;
		goto error_term;
	}
	srx->fpdu_part_rem -= rv;
	srx->fpdu_part_rcvd += rv;
	wqe->processed += rv;

	if (!srx->fpdu_part_rem) {
		srx->ddp_to += srx->fpdu_part_rcvd;
		return 0;
	}
	return -EAGAIN;

error_term:
	siw_init_terminate(qp, TERM_ERROR_LAYER_DDP, DDP_ETYPE_CATASTROPHIC,
			   DDP_ECODE_CATASTROPHIC, 0);
	return rv;
}