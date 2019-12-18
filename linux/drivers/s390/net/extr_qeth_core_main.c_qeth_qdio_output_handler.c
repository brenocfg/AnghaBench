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
struct qeth_qdio_out_q {int /*<<< orphan*/  used_buffers; struct qeth_qdio_out_buffer** bufs; } ;
struct qeth_qdio_out_buffer {int dummy; } ;
struct TYPE_2__ {struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {struct net_device* dev; TYPE_1__ qdio; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 unsigned int QDIO_ERROR_FATAL ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  qeth_check_outbound_queue (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  qeth_clear_output_buffer (struct qeth_qdio_out_q*,struct qeth_qdio_out_buffer*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_handle_send_error (struct qeth_card*,struct qeth_qdio_out_buffer*,unsigned int) ; 
 int /*<<< orphan*/  qeth_out_queue_is_full (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 

__attribute__((used)) static void qeth_qdio_output_handler(struct ccw_device *ccwdev,
				     unsigned int qdio_error, int __queue,
				     int first_element, int count,
				     unsigned long card_ptr)
{
	struct qeth_card *card        = (struct qeth_card *) card_ptr;
	struct qeth_qdio_out_q *queue = card->qdio.out_qs[__queue];
	struct qeth_qdio_out_buffer *buffer;
	struct net_device *dev = card->dev;
	struct netdev_queue *txq;
	int i;

	QETH_CARD_TEXT(card, 6, "qdouhdl");
	if (qdio_error & QDIO_ERROR_FATAL) {
		QETH_CARD_TEXT(card, 2, "achkcond");
		netif_tx_stop_all_queues(dev);
		qeth_schedule_recovery(card);
		return;
	}

	for (i = first_element; i < (first_element + count); ++i) {
		int bidx = i % QDIO_MAX_BUFFERS_PER_Q;
		buffer = queue->bufs[bidx];
		qeth_handle_send_error(card, buffer, qdio_error);
		qeth_clear_output_buffer(queue, buffer, qdio_error, 0);
	}

	atomic_sub(count, &queue->used_buffers);
	qeth_check_outbound_queue(queue);

	txq = netdev_get_tx_queue(dev, __queue);
	/* xmit may have observed the full-condition, but not yet stopped the
	 * txq. In which case the code below won't trigger. So before returning,
	 * xmit will re-check the txq's fill level and wake it up if needed.
	 */
	if (netif_tx_queue_stopped(txq) && !qeth_out_queue_is_full(queue))
		netif_tx_wake_queue(txq);
}