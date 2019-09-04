#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct rvt_cq_wc {unsigned int head; unsigned int tail; struct ib_wc* kqueue; TYPE_6__* uqueue; } ;
struct TYPE_8__ {unsigned int cqe; int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct rvt_cq {scalar_t__ notify; int /*<<< orphan*/  lock; int /*<<< orphan*/  comptask; int /*<<< orphan*/  comp_vector_cpu; int /*<<< orphan*/  triggered; scalar_t__ ip; TYPE_2__ ibcq; struct rvt_cq_wc* queue; } ;
struct TYPE_10__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  port_num; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  wc_flags; int /*<<< orphan*/  src_qp; TYPE_5__* qp; TYPE_4__ ex; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wr_id; } ;
struct TYPE_7__ {TYPE_2__* cq; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_12__ {scalar_t__ status; int /*<<< orphan*/  port_num; int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  wc_flags; int /*<<< orphan*/  src_qp; int /*<<< orphan*/  qp_num; TYPE_3__ ex; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wr_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 scalar_t__ IB_CQ_NEXT_COMP ; 
 scalar_t__ IB_CQ_SOLICITED ; 
 int /*<<< orphan*/  IB_EVENT_CQ_ERR ; 
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ RVT_CQ_NONE ; 
 int /*<<< orphan*/  comp_vector_wq ; 
 int /*<<< orphan*/  ib_lid_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rvt_cq_enter (struct rvt_cq*,struct ib_wc*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void rvt_cq_enter(struct rvt_cq *cq, struct ib_wc *entry, bool solicited)
{
	struct rvt_cq_wc *wc;
	unsigned long flags;
	u32 head;
	u32 next;

	spin_lock_irqsave(&cq->lock, flags);

	/*
	 * Note that the head pointer might be writable by user processes.
	 * Take care to verify it is a sane value.
	 */
	wc = cq->queue;
	head = wc->head;
	if (head >= (unsigned)cq->ibcq.cqe) {
		head = cq->ibcq.cqe;
		next = 0;
	} else {
		next = head + 1;
	}

	if (unlikely(next == wc->tail)) {
		spin_unlock_irqrestore(&cq->lock, flags);
		if (cq->ibcq.event_handler) {
			struct ib_event ev;

			ev.device = cq->ibcq.device;
			ev.element.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_ERR;
			cq->ibcq.event_handler(&ev, cq->ibcq.cq_context);
		}
		return;
	}
	trace_rvt_cq_enter(cq, entry, head);
	if (cq->ip) {
		wc->uqueue[head].wr_id = entry->wr_id;
		wc->uqueue[head].status = entry->status;
		wc->uqueue[head].opcode = entry->opcode;
		wc->uqueue[head].vendor_err = entry->vendor_err;
		wc->uqueue[head].byte_len = entry->byte_len;
		wc->uqueue[head].ex.imm_data = entry->ex.imm_data;
		wc->uqueue[head].qp_num = entry->qp->qp_num;
		wc->uqueue[head].src_qp = entry->src_qp;
		wc->uqueue[head].wc_flags = entry->wc_flags;
		wc->uqueue[head].pkey_index = entry->pkey_index;
		wc->uqueue[head].slid = ib_lid_cpu16(entry->slid);
		wc->uqueue[head].sl = entry->sl;
		wc->uqueue[head].dlid_path_bits = entry->dlid_path_bits;
		wc->uqueue[head].port_num = entry->port_num;
		/* Make sure entry is written before the head index. */
		smp_wmb();
	} else {
		wc->kqueue[head] = *entry;
	}
	wc->head = next;

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
}