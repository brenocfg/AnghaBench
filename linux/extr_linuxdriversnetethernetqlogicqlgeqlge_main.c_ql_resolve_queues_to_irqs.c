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
struct ql_adapter {int intr_count; TYPE_2__* ndev; TYPE_1__* rx_ring; int /*<<< orphan*/  flags; struct intr_context* intr_context; } ;
struct intr_context {int intr; int intr_en_mask; int intr_dis_mask; int intr_read_mask; int /*<<< orphan*/  name; void* handler; struct ql_adapter* qdev; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int irq; } ;

/* Variables and functions */
 int INTR_EN_IHD ; 
 int INTR_EN_IHD_MASK ; 
 int INTR_EN_INTR_MASK ; 
 int INTR_EN_TYPE_DISABLE ; 
 int INTR_EN_TYPE_ENABLE ; 
 int INTR_EN_TYPE_MASK ; 
 int INTR_EN_TYPE_READ ; 
 int /*<<< orphan*/  QL_MSIX_ENABLED ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_set_irq_mask (struct ql_adapter*,struct intr_context*) ; 
 int /*<<< orphan*/  ql_set_tx_vect (struct ql_adapter*) ; 
 void* qlge_isr ; 
 void* qlge_msix_rx_isr ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_resolve_queues_to_irqs(struct ql_adapter *qdev)
{
	int i = 0;
	struct intr_context *intr_context = &qdev->intr_context[0];

	if (likely(test_bit(QL_MSIX_ENABLED, &qdev->flags))) {
		/* Each rx_ring has it's
		 * own intr_context since we have separate
		 * vectors for each queue.
		 */
		for (i = 0; i < qdev->intr_count; i++, intr_context++) {
			qdev->rx_ring[i].irq = i;
			intr_context->intr = i;
			intr_context->qdev = qdev;
			/* Set up this vector's bit-mask that indicates
			 * which queues it services.
			 */
			ql_set_irq_mask(qdev, intr_context);
			/*
			 * We set up each vectors enable/disable/read bits so
			 * there's no bit/mask calculations in the critical path.
			 */
			intr_context->intr_en_mask =
			    INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
			    INTR_EN_TYPE_ENABLE | INTR_EN_IHD_MASK | INTR_EN_IHD
			    | i;
			intr_context->intr_dis_mask =
			    INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
			    INTR_EN_TYPE_DISABLE | INTR_EN_IHD_MASK |
			    INTR_EN_IHD | i;
			intr_context->intr_read_mask =
			    INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
			    INTR_EN_TYPE_READ | INTR_EN_IHD_MASK | INTR_EN_IHD |
			    i;
			if (i == 0) {
				/* The first vector/queue handles
				 * broadcast/multicast, fatal errors,
				 * and firmware events.  This in addition
				 * to normal inbound NAPI processing.
				 */
				intr_context->handler = qlge_isr;
				sprintf(intr_context->name, "%s-rx-%d",
					qdev->ndev->name, i);
			} else {
				/*
				 * Inbound queues handle unicast frames only.
				 */
				intr_context->handler = qlge_msix_rx_isr;
				sprintf(intr_context->name, "%s-rx-%d",
					qdev->ndev->name, i);
			}
		}
	} else {
		/*
		 * All rx_rings use the same intr_context since
		 * there is only one vector.
		 */
		intr_context->intr = 0;
		intr_context->qdev = qdev;
		/*
		 * We set up each vectors enable/disable/read bits so
		 * there's no bit/mask calculations in the critical path.
		 */
		intr_context->intr_en_mask =
		    INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK | INTR_EN_TYPE_ENABLE;
		intr_context->intr_dis_mask =
		    INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK |
		    INTR_EN_TYPE_DISABLE;
		intr_context->intr_read_mask =
		    INTR_EN_TYPE_MASK | INTR_EN_INTR_MASK | INTR_EN_TYPE_READ;
		/*
		 * Single interrupt means one handler for all rings.
		 */
		intr_context->handler = qlge_isr;
		sprintf(intr_context->name, "%s-single_irq", qdev->ndev->name);
		/* Set up this vector's bit-mask that indicates
		 * which queues it services. In this case there is
		 * a single vector so it will service all RSS and
		 * TX completion rings.
		 */
		ql_set_irq_mask(qdev, intr_context);
	}
	/* Tell the TX completion rings which MSIx vector
	 * they will be using.
	 */
	ql_set_tx_vect(qdev);
}