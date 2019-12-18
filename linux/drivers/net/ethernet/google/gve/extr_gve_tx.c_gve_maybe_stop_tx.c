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
struct sk_buff {int dummy; } ;
struct gve_tx_ring {int /*<<< orphan*/  wake_queue; int /*<<< orphan*/  netdev_txq; int /*<<< orphan*/  stop_queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int gve_can_tx (struct gve_tx_ring*,int) ; 
 int gve_skb_fifo_bytes_required (struct gve_tx_ring*,struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_tx_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static int gve_maybe_stop_tx(struct gve_tx_ring *tx, struct sk_buff *skb)
{
	int bytes_required;

	bytes_required = gve_skb_fifo_bytes_required(tx, skb);
	if (likely(gve_can_tx(tx, bytes_required)))
		return 0;

	/* No space, so stop the queue */
	tx->stop_queue++;
	netif_tx_stop_queue(tx->netdev_txq);
	smp_mb();	/* sync with restarting queue in gve_clean_tx_done() */

	/* Now check for resources again, in case gve_clean_tx_done() freed
	 * resources after we checked and we stopped the queue after
	 * gve_clean_tx_done() checked.
	 *
	 * gve_maybe_stop_tx()			gve_clean_tx_done()
	 *   nsegs/can_alloc test failed
	 *					  gve_tx_free_fifo()
	 *					  if (tx queue stopped)
	 *					    netif_tx_queue_wake()
	 *   netif_tx_stop_queue()
	 *   Need to check again for space here!
	 */
	if (likely(!gve_can_tx(tx, bytes_required)))
		return -EBUSY;

	netif_tx_start_queue(tx->netdev_txq);
	tx->wake_queue++;
	return 0;
}