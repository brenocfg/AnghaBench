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
struct pvrdma_ring {int /*<<< orphan*/  cons_head; } ;
struct pvrdma_eqe {int type; int info; } ;
struct pvrdma_dev {int /*<<< orphan*/  ib_active; TYPE_4__* pdev; TYPE_3__* dsr; TYPE_1__* async_ring_state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int num_pages; } ;
struct TYPE_7__ {TYPE_2__ async_ring_pages; } ;
struct TYPE_5__ {struct pvrdma_ring rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PAGE_SIZE ; 
#define  PVRDMA_EVENT_CLIENT_REREGISTER 146 
#define  PVRDMA_EVENT_COMM_EST 145 
#define  PVRDMA_EVENT_CQ_ERR 144 
#define  PVRDMA_EVENT_DEVICE_FATAL 143 
#define  PVRDMA_EVENT_GID_CHANGE 142 
#define  PVRDMA_EVENT_LID_CHANGE 141 
#define  PVRDMA_EVENT_PATH_MIG 140 
#define  PVRDMA_EVENT_PATH_MIG_ERR 139 
#define  PVRDMA_EVENT_PKEY_CHANGE 138 
#define  PVRDMA_EVENT_PORT_ACTIVE 137 
#define  PVRDMA_EVENT_PORT_ERR 136 
#define  PVRDMA_EVENT_QP_ACCESS_ERR 135 
#define  PVRDMA_EVENT_QP_FATAL 134 
#define  PVRDMA_EVENT_QP_LAST_WQE_REACHED 133 
#define  PVRDMA_EVENT_QP_REQ_ERR 132 
#define  PVRDMA_EVENT_SM_CHANGE 131 
#define  PVRDMA_EVENT_SQ_DRAINED 130 
#define  PVRDMA_EVENT_SRQ_ERR 129 
#define  PVRDMA_EVENT_SRQ_LIMIT_REACHED 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct pvrdma_eqe* get_eqe (struct pvrdma_dev*,unsigned int) ; 
 int /*<<< orphan*/  pvrdma_cq_event (struct pvrdma_dev*,int,int) ; 
 int /*<<< orphan*/  pvrdma_dev_event (struct pvrdma_dev*,int,int) ; 
 scalar_t__ pvrdma_idx_ring_has_data (struct pvrdma_ring*,int,unsigned int*) ; 
 int /*<<< orphan*/  pvrdma_idx_ring_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvrdma_qp_event (struct pvrdma_dev*,int,int) ; 
 int /*<<< orphan*/  pvrdma_srq_event (struct pvrdma_dev*,int,int) ; 

__attribute__((used)) static irqreturn_t pvrdma_intr1_handler(int irq, void *dev_id)
{
	struct pvrdma_dev *dev = dev_id;
	struct pvrdma_ring *ring = &dev->async_ring_state->rx;
	int ring_slots = (dev->dsr->async_ring_pages.num_pages - 1) *
			 PAGE_SIZE / sizeof(struct pvrdma_eqe);
	unsigned int head;

	dev_dbg(&dev->pdev->dev, "interrupt 1 (async event) handler\n");

	/*
	 * Don't process events until the IB device is registered. Otherwise
	 * we'll try to ib_dispatch_event() on an invalid device.
	 */
	if (!dev->ib_active)
		return IRQ_HANDLED;

	while (pvrdma_idx_ring_has_data(ring, ring_slots, &head) > 0) {
		struct pvrdma_eqe *eqe;

		eqe = get_eqe(dev, head);

		switch (eqe->type) {
		case PVRDMA_EVENT_QP_FATAL:
		case PVRDMA_EVENT_QP_REQ_ERR:
		case PVRDMA_EVENT_QP_ACCESS_ERR:
		case PVRDMA_EVENT_COMM_EST:
		case PVRDMA_EVENT_SQ_DRAINED:
		case PVRDMA_EVENT_PATH_MIG:
		case PVRDMA_EVENT_PATH_MIG_ERR:
		case PVRDMA_EVENT_QP_LAST_WQE_REACHED:
			pvrdma_qp_event(dev, eqe->info, eqe->type);
			break;

		case PVRDMA_EVENT_CQ_ERR:
			pvrdma_cq_event(dev, eqe->info, eqe->type);
			break;

		case PVRDMA_EVENT_SRQ_ERR:
		case PVRDMA_EVENT_SRQ_LIMIT_REACHED:
			pvrdma_srq_event(dev, eqe->info, eqe->type);
			break;

		case PVRDMA_EVENT_PORT_ACTIVE:
		case PVRDMA_EVENT_PORT_ERR:
		case PVRDMA_EVENT_LID_CHANGE:
		case PVRDMA_EVENT_PKEY_CHANGE:
		case PVRDMA_EVENT_SM_CHANGE:
		case PVRDMA_EVENT_CLIENT_REREGISTER:
		case PVRDMA_EVENT_GID_CHANGE:
			pvrdma_dev_event(dev, eqe->info, eqe->type);
			break;

		case PVRDMA_EVENT_DEVICE_FATAL:
			pvrdma_dev_event(dev, 1, eqe->type);
			break;

		default:
			break;
		}

		pvrdma_idx_ring_inc(&ring->cons_head, ring_slots);
	}

	return IRQ_HANDLED;
}