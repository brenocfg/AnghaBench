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
struct sge_txq {int size; int /*<<< orphan*/  restarts; int /*<<< orphan*/  in_use; } ;
struct sge_eth_txq {int /*<<< orphan*/  txq; struct sge_txq q; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_tx_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_tx_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (int /*<<< orphan*/ ) ; 
 unsigned int reclaim_completed_tx (struct adapter*,struct sge_txq*,int,int) ; 
 int txq_avail (struct sge_txq*) ; 

int t4_sge_eth_txq_egress_update(struct adapter *adap, struct sge_eth_txq *eq,
				 int maxreclaim)
{
	struct sge_txq *q = &eq->q;
	unsigned int reclaimed;

	if (!q->in_use || !__netif_tx_trylock(eq->txq))
		return 0;

	/* Reclaim pending completed TX Descriptors. */
	reclaimed = reclaim_completed_tx(adap, &eq->q, maxreclaim, true);

	/* If the TX Queue is currently stopped and there's now more than half
	 * the queue available, restart it.  Otherwise bail out since the rest
	 * of what we want do here is with the possibility of shipping any
	 * currently buffered Coalesced TX Work Request.
	 */
	if (netif_tx_queue_stopped(eq->txq) && txq_avail(q) > (q->size / 2)) {
		netif_tx_wake_queue(eq->txq);
		eq->q.restarts++;
	}

	__netif_tx_unlock(eq->txq);
	return reclaimed;
}