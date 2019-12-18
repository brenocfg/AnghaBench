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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct regpair {int lo; scalar_t__ hi; } ;
struct ib_srq {int /*<<< orphan*/  srq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct qedr_srq {struct ib_srq ibsrq; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct ib_cq {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct qedr_qp {struct ib_qp ibqp; struct ib_cq ibcq; } ;
struct qedr_dev {int /*<<< orphan*/  srqs; } ;
struct qedr_cq {struct ib_qp ibqp; struct ib_cq ibcq; } ;
struct TYPE_2__ {struct ib_srq* srq; struct ib_qp* qp; struct ib_cq* cq; } ;
struct ib_event {TYPE_1__ element; int /*<<< orphan*/  device; void* event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int,...) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qedr_dev*,char*,int,...) ; 
#define  EVENT_TYPE_CQ 139 
 int EVENT_TYPE_NOT_DEFINED ; 
#define  EVENT_TYPE_QP 138 
#define  EVENT_TYPE_SRQ 137 
 void* IB_EVENT_CQ_ERR ; 
 void* IB_EVENT_QP_ACCESS_ERR ; 
 void* IB_EVENT_QP_FATAL ; 
 void* IB_EVENT_QP_REQ_ERR ; 
 void* IB_EVENT_SQ_DRAINED ; 
 void* IB_EVENT_SRQ_ERR ; 
 void* IB_EVENT_SRQ_LIMIT_REACHED ; 
 scalar_t__ IS_ROCE (struct qedr_dev*) ; 
#define  QED_IWARP_EVENT_SRQ_EMPTY 136 
#define  QED_IWARP_EVENT_SRQ_LIMIT 135 
#define  ROCE_ASYNC_EVENT_CQ_OVERFLOW_ERR 134 
#define  ROCE_ASYNC_EVENT_LOCAL_ACCESS_ERR 133 
#define  ROCE_ASYNC_EVENT_LOCAL_INVALID_REQUEST_ERR 132 
#define  ROCE_ASYNC_EVENT_QP_CATASTROPHIC_ERR 131 
#define  ROCE_ASYNC_EVENT_SQ_DRAINED 130 
#define  ROCE_ASYNC_EVENT_SRQ_EMPTY 129 
#define  ROCE_ASYNC_EVENT_SRQ_LIMIT 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ib_event*,int /*<<< orphan*/ ) ; 
 struct qedr_srq* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qedr_affiliated_event(void *context, u8 e_code, void *fw_handle)
{
#define EVENT_TYPE_NOT_DEFINED	0
#define EVENT_TYPE_CQ		1
#define EVENT_TYPE_QP		2
#define EVENT_TYPE_SRQ		3
	struct qedr_dev *dev = (struct qedr_dev *)context;
	struct regpair *async_handle = (struct regpair *)fw_handle;
	u64 roce_handle64 = ((u64) async_handle->hi << 32) + async_handle->lo;
	u8 event_type = EVENT_TYPE_NOT_DEFINED;
	struct ib_event event;
	struct ib_srq *ibsrq;
	struct qedr_srq *srq;
	unsigned long flags;
	struct ib_cq *ibcq;
	struct ib_qp *ibqp;
	struct qedr_cq *cq;
	struct qedr_qp *qp;
	u16 srq_id;

	if (IS_ROCE(dev)) {
		switch (e_code) {
		case ROCE_ASYNC_EVENT_CQ_OVERFLOW_ERR:
			event.event = IB_EVENT_CQ_ERR;
			event_type = EVENT_TYPE_CQ;
			break;
		case ROCE_ASYNC_EVENT_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			event_type = EVENT_TYPE_QP;
			break;
		case ROCE_ASYNC_EVENT_QP_CATASTROPHIC_ERR:
			event.event = IB_EVENT_QP_FATAL;
			event_type = EVENT_TYPE_QP;
			break;
		case ROCE_ASYNC_EVENT_LOCAL_INVALID_REQUEST_ERR:
			event.event = IB_EVENT_QP_REQ_ERR;
			event_type = EVENT_TYPE_QP;
			break;
		case ROCE_ASYNC_EVENT_LOCAL_ACCESS_ERR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			event_type = EVENT_TYPE_QP;
			break;
		case ROCE_ASYNC_EVENT_SRQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			event_type = EVENT_TYPE_SRQ;
			break;
		case ROCE_ASYNC_EVENT_SRQ_EMPTY:
			event.event = IB_EVENT_SRQ_ERR;
			event_type = EVENT_TYPE_SRQ;
			break;
		default:
			DP_ERR(dev, "unsupported event %d on handle=%llx\n",
			       e_code, roce_handle64);
		}
	} else {
		switch (e_code) {
		case QED_IWARP_EVENT_SRQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			event_type = EVENT_TYPE_SRQ;
			break;
		case QED_IWARP_EVENT_SRQ_EMPTY:
			event.event = IB_EVENT_SRQ_ERR;
			event_type = EVENT_TYPE_SRQ;
			break;
		default:
		DP_ERR(dev, "unsupported event %d on handle=%llx\n", e_code,
		       roce_handle64);
		}
	}
	switch (event_type) {
	case EVENT_TYPE_CQ:
		cq = (struct qedr_cq *)(uintptr_t)roce_handle64;
		if (cq) {
			ibcq = &cq->ibcq;
			if (ibcq->event_handler) {
				event.device = ibcq->device;
				event.element.cq = ibcq;
				ibcq->event_handler(&event, ibcq->cq_context);
			}
		} else {
			WARN(1,
			     "Error: CQ event with NULL pointer ibcq. Handle=%llx\n",
			     roce_handle64);
		}
		DP_ERR(dev, "CQ event %d on handle %p\n", e_code, cq);
		break;
	case EVENT_TYPE_QP:
		qp = (struct qedr_qp *)(uintptr_t)roce_handle64;
		if (qp) {
			ibqp = &qp->ibqp;
			if (ibqp->event_handler) {
				event.device = ibqp->device;
				event.element.qp = ibqp;
				ibqp->event_handler(&event, ibqp->qp_context);
			}
		} else {
			WARN(1,
			     "Error: QP event with NULL pointer ibqp. Handle=%llx\n",
			     roce_handle64);
		}
		DP_ERR(dev, "QP event %d on handle %p\n", e_code, qp);
		break;
	case EVENT_TYPE_SRQ:
		srq_id = (u16)roce_handle64;
		xa_lock_irqsave(&dev->srqs, flags);
		srq = xa_load(&dev->srqs, srq_id);
		if (srq) {
			ibsrq = &srq->ibsrq;
			if (ibsrq->event_handler) {
				event.device = ibsrq->device;
				event.element.srq = ibsrq;
				ibsrq->event_handler(&event,
						     ibsrq->srq_context);
			}
		} else {
			DP_NOTICE(dev,
				  "SRQ event with NULL pointer ibsrq. Handle=%llx\n",
				  roce_handle64);
		}
		xa_unlock_irqrestore(&dev->srqs, flags);
		DP_NOTICE(dev, "SRQ event %d on handle %p\n", e_code, srq);
	default:
		break;
	}
}