#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  scalar_t__ uint32_t ;
struct siw_sqe {int num_sge; int /*<<< orphan*/  flags; scalar_t__ rkey; void* raddr; TYPE_3__* sge; int /*<<< orphan*/  opcode; } ;
struct siw_wqe {scalar_t__ wr_status; struct siw_sqe sqe; int /*<<< orphan*/ ** mem; scalar_t__ processed; } ;
struct TYPE_5__ {int /*<<< orphan*/  ddp_msn; int /*<<< orphan*/  sink_stag; int /*<<< orphan*/  source_stag; int /*<<< orphan*/  read_size; int /*<<< orphan*/  source_to; int /*<<< orphan*/  sink_to; } ;
struct TYPE_6__ {TYPE_1__ rreq; } ;
struct siw_rx_stream {scalar_t__* ddp_msn; TYPE_2__ hdr; } ;
struct TYPE_8__ {int irq_size; } ;
struct siw_qp {int irq_put; int /*<<< orphan*/  sq_lock; TYPE_4__ attrs; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ lkey; void* laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDP_ECODE_UT_INVALID_MSN_RANGE ; 
 int /*<<< orphan*/  DDP_ETYPE_UNTAGGED_BUF ; 
 int EPROTO ; 
 int /*<<< orphan*/  RDMAP_ECODE_CATASTROPHIC_STREAM ; 
 int /*<<< orphan*/  RDMAP_ETYPE_REMOTE_OPERATION ; 
 size_t RDMAP_UNTAGGED_QN_RDMA_READ ; 
 int /*<<< orphan*/  SIW_OP_READ_RESPONSE ; 
 int /*<<< orphan*/  SIW_WQE_VALID ; 
 scalar_t__ SIW_WR_IDLE ; 
 scalar_t__ SIW_WR_QUEUED ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_DDP ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_RDMAP ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct siw_sqe* irq_alloc_free (struct siw_qp*) ; 
 scalar_t__ likely (struct siw_sqe*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qp_id (struct siw_qp*) ; 
 int /*<<< orphan*/  siw_init_terminate (struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int siw_sq_start (struct siw_qp*) ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct siw_wqe* tx_wqe (struct siw_qp*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int siw_init_rresp(struct siw_qp *qp, struct siw_rx_stream *srx)
{
	struct siw_wqe *tx_work = tx_wqe(qp);
	struct siw_sqe *resp;

	uint64_t raddr = be64_to_cpu(srx->hdr.rreq.sink_to),
		 laddr = be64_to_cpu(srx->hdr.rreq.source_to);
	uint32_t length = be32_to_cpu(srx->hdr.rreq.read_size),
		 lkey = be32_to_cpu(srx->hdr.rreq.source_stag),
		 rkey = be32_to_cpu(srx->hdr.rreq.sink_stag),
		 msn = be32_to_cpu(srx->hdr.rreq.ddp_msn);

	int run_sq = 1, rv = 0;
	unsigned long flags;

	if (unlikely(msn != srx->ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ])) {
		siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
				   DDP_ETYPE_UNTAGGED_BUF,
				   DDP_ECODE_UT_INVALID_MSN_RANGE, 0);
		return -EPROTO;
	}
	spin_lock_irqsave(&qp->sq_lock, flags);

	if (tx_work->wr_status == SIW_WR_IDLE) {
		/*
		 * immediately schedule READ response w/o
		 * consuming IRQ entry: IRQ must be empty.
		 */
		tx_work->processed = 0;
		tx_work->mem[0] = NULL;
		tx_work->wr_status = SIW_WR_QUEUED;
		resp = &tx_work->sqe;
	} else {
		resp = irq_alloc_free(qp);
		run_sq = 0;
	}
	if (likely(resp)) {
		resp->opcode = SIW_OP_READ_RESPONSE;

		resp->sge[0].length = length;
		resp->sge[0].laddr = laddr;
		resp->sge[0].lkey = lkey;

		/* Keep aside message sequence number for potential
		 * error reporting during Read Response generation.
		 */
		resp->sge[1].length = msn;

		resp->raddr = raddr;
		resp->rkey = rkey;
		resp->num_sge = length ? 1 : 0;

		/* RRESP now valid as current TX wqe or placed into IRQ */
		smp_store_mb(resp->flags, SIW_WQE_VALID);
	} else {
		pr_warn("siw: [QP %u]: irq %d exceeded %d\n", qp_id(qp),
			qp->irq_put % qp->attrs.irq_size, qp->attrs.irq_size);

		siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
				   RDMAP_ETYPE_REMOTE_OPERATION,
				   RDMAP_ECODE_CATASTROPHIC_STREAM, 0);
		rv = -EPROTO;
	}

	spin_unlock_irqrestore(&qp->sq_lock, flags);

	if (run_sq)
		rv = siw_sq_start(qp);

	return rv;
}