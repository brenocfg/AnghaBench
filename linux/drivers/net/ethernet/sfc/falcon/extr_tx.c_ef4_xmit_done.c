#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ef4_tx_queue {unsigned int ptr_mask; unsigned int pkts_compl; unsigned int bytes_compl; int insert_count; int read_count; int old_write_count; int empty_read_count; int /*<<< orphan*/  write_count; int /*<<< orphan*/  core_txq; int /*<<< orphan*/  merge_events; struct ef4_nic* efx; } ;
struct ef4_nic {unsigned int txq_wake_thresh; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  port_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int) ; 
 int EF4_EMPTY_COUNT_VALID ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_dequeue_buffers (struct ef4_tx_queue*,unsigned int,unsigned int*,unsigned int*) ; 
 struct ef4_tx_queue* ef4_tx_queue_partner (struct ef4_tx_queue*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 unsigned int max (int,int) ; 
 int /*<<< orphan*/  netif_device_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void ef4_xmit_done(struct ef4_tx_queue *tx_queue, unsigned int index)
{
	unsigned fill_level;
	struct ef4_nic *efx = tx_queue->efx;
	struct ef4_tx_queue *txq2;
	unsigned int pkts_compl = 0, bytes_compl = 0;

	EF4_BUG_ON_PARANOID(index > tx_queue->ptr_mask);

	ef4_dequeue_buffers(tx_queue, index, &pkts_compl, &bytes_compl);
	tx_queue->pkts_compl += pkts_compl;
	tx_queue->bytes_compl += bytes_compl;

	if (pkts_compl > 1)
		++tx_queue->merge_events;

	/* See if we need to restart the netif queue.  This memory
	 * barrier ensures that we write read_count (inside
	 * ef4_dequeue_buffers()) before reading the queue status.
	 */
	smp_mb();
	if (unlikely(netif_tx_queue_stopped(tx_queue->core_txq)) &&
	    likely(efx->port_enabled) &&
	    likely(netif_device_present(efx->net_dev))) {
		txq2 = ef4_tx_queue_partner(tx_queue);
		fill_level = max(tx_queue->insert_count - tx_queue->read_count,
				 txq2->insert_count - txq2->read_count);
		if (fill_level <= efx->txq_wake_thresh)
			netif_tx_wake_queue(tx_queue->core_txq);
	}

	/* Check whether the hardware queue is now empty */
	if ((int)(tx_queue->read_count - tx_queue->old_write_count) >= 0) {
		tx_queue->old_write_count = READ_ONCE(tx_queue->write_count);
		if (tx_queue->read_count == tx_queue->old_write_count) {
			smp_mb();
			tx_queue->empty_read_count =
				tx_queue->read_count | EF4_EMPTY_COUNT_VALID;
		}
	}
}