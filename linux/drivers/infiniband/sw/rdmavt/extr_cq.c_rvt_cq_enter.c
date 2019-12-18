#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct rvt_k_cq_wc {unsigned int head; unsigned int tail; struct ib_wc* kqueue; } ;
struct rvt_dev_info {int dummy; } ;
struct rvt_cq_wc {int /*<<< orphan*/  head; int /*<<< orphan*/  tail; struct ib_uverbs_wc* uqueue; } ;
struct TYPE_7__ {unsigned int cqe; int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct rvt_cq {int cq_full; scalar_t__ notify; int /*<<< orphan*/  lock; int /*<<< orphan*/  comptask; int /*<<< orphan*/  comp_vector_cpu; int /*<<< orphan*/  triggered; TYPE_2__ ibcq; struct rvt_dev_info* rdi; struct rvt_k_cq_wc* kqueue; struct rvt_cq_wc* queue; scalar_t__ ip; } ;
struct TYPE_9__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  port_num; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  wc_flags; int /*<<< orphan*/  src_qp; TYPE_5__* qp; TYPE_4__ ex; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wr_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  imm_data; } ;
struct ib_uverbs_wc {scalar_t__ status; int /*<<< orphan*/  port_num; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  wc_flags; int /*<<< orphan*/  src_qp; int /*<<< orphan*/  qp_num; TYPE_3__ ex; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wr_id; } ;
struct TYPE_6__ {TYPE_2__* cq; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 scalar_t__ IB_CQ_NEXT_COMP ; 
 scalar_t__ IB_CQ_SOLICITED ; 
 int /*<<< orphan*/  IB_EVENT_CQ_ERR ; 
 scalar_t__ IB_WC_SUCCESS ; 
 unsigned int RDMA_READ_UAPI_ATOMIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_WRITE_UAPI_ATOMIC (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ RVT_CQ_NONE ; 
 int /*<<< orphan*/  comp_vector_wq ; 
 int /*<<< orphan*/  ib_lid_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_pr_err_ratelimited (struct rvt_dev_info*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rvt_cq_enter (struct rvt_cq*,struct ib_wc*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

bool rvt_cq_enter(struct rvt_cq *cq, struct ib_wc *entry, bool solicited)
{
	struct ib_uverbs_wc *uqueue = NULL;
	struct ib_wc *kqueue = NULL;
	struct rvt_cq_wc *u_wc = NULL;
	struct rvt_k_cq_wc *k_wc = NULL;
	unsigned long flags;
	u32 head;
	u32 next;
	u32 tail;

	spin_lock_irqsave(&cq->lock, flags);

	if (cq->ip) {
		u_wc = cq->queue;
		uqueue = &u_wc->uqueue[0];
		head = RDMA_READ_UAPI_ATOMIC(u_wc->head);
		tail = RDMA_READ_UAPI_ATOMIC(u_wc->tail);
	} else {
		k_wc = cq->kqueue;
		kqueue = &k_wc->kqueue[0];
		head = k_wc->head;
		tail = k_wc->tail;
	}

	/*
	 * Note that the head pointer might be writable by
	 * user processes.Take care to verify it is a sane value.
	 */
	if (head >= (unsigned)cq->ibcq.cqe) {
		head = cq->ibcq.cqe;
		next = 0;
	} else {
		next = head + 1;
	}

	if (unlikely(next == tail || cq->cq_full)) {
		struct rvt_dev_info *rdi = cq->rdi;

		if (!cq->cq_full)
			rvt_pr_err_ratelimited(rdi, "CQ is full!\n");
		cq->cq_full = true;
		spin_unlock_irqrestore(&cq->lock, flags);
		if (cq->ibcq.event_handler) {
			struct ib_event ev;

			ev.device = cq->ibcq.device;
			ev.element.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_ERR;
			cq->ibcq.event_handler(&ev, cq->ibcq.cq_context);
		}
		return false;
	}
	trace_rvt_cq_enter(cq, entry, head);
	if (uqueue) {
		uqueue[head].wr_id = entry->wr_id;
		uqueue[head].status = entry->status;
		uqueue[head].opcode = entry->opcode;
		uqueue[head].vendor_err = entry->vendor_err;
		uqueue[head].byte_len = entry->byte_len;
		uqueue[head].ex.imm_data = entry->ex.imm_data;
		uqueue[head].qp_num = entry->qp->qp_num;
		uqueue[head].src_qp = entry->src_qp;
		uqueue[head].wc_flags = entry->wc_flags;
		uqueue[head].pkey_index = entry->pkey_index;
		uqueue[head].slid = ib_lid_cpu16(entry->slid);
		uqueue[head].sl = entry->sl;
		uqueue[head].dlid_path_bits = entry->dlid_path_bits;
		uqueue[head].port_num = entry->port_num;
		/* Make sure entry is written before the head index. */
		RDMA_WRITE_UAPI_ATOMIC(u_wc->head, next);
	} else {
		kqueue[head] = *entry;
		k_wc->head = next;
	}

	if (cq->notify == IB_CQ_NEXT_COMP ||
	    (cq->notify == IB_CQ_SOLICITED &&
	     (solicited || entry->status != IB_WC_SUCCESS))) {
		/*
		 * This will cause send_complete() to be called in
		 * another thread.
		 */
		cq->notify = RVT_CQ_NONE;
		cq->triggered++;
		queue_work_on(cq->comp_vector_cpu, comp_vector_wq,
			      &cq->comptask);
	}

	spin_unlock_irqrestore(&cq->lock, flags);
	return true;
}