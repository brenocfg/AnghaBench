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
struct TYPE_2__ {unsigned int num; int /*<<< orphan*/  completed; int /*<<< orphan*/ * idx; struct gnttab_copy* op; } ;
struct xenvif_queue {TYPE_1__ rx_copy; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  rx; } ;
struct xen_netif_rx_response {scalar_t__ status; } ;
struct gnttab_copy {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ GNTST_okay ; 
 struct xen_netif_rx_response* RING_GET_RESPONSE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_batch_copy (struct gnttab_copy*,unsigned int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void xenvif_rx_copy_flush(struct xenvif_queue *queue)
{
	unsigned int i;
	int notify;

	gnttab_batch_copy(queue->rx_copy.op, queue->rx_copy.num);

	for (i = 0; i < queue->rx_copy.num; i++) {
		struct gnttab_copy *op;

		op = &queue->rx_copy.op[i];

		/* If the copy failed, overwrite the status field in
		 * the corresponding response.
		 */
		if (unlikely(op->status != GNTST_okay)) {
			struct xen_netif_rx_response *rsp;

			rsp = RING_GET_RESPONSE(&queue->rx,
						queue->rx_copy.idx[i]);
			rsp->status = op->status;
		}
	}

	queue->rx_copy.num = 0;

	/* Push responses for all completed packets. */
	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&queue->rx, notify);
	if (notify)
		notify_remote_via_irq(queue->rx_irq);

	__skb_queue_purge(queue->rx_copy.completed);
}