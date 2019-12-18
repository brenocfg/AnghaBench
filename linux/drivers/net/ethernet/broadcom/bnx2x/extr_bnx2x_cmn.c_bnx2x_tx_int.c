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
typedef  scalar_t__ u16 ;
struct netdev_queue {int dummy; } ;
struct bnx2x_fp_txdata {scalar_t__ tx_bd_cons; scalar_t__ tx_pkt_cons; int /*<<< orphan*/  txq_index; int /*<<< orphan*/ * tx_cons_sb; } ;
struct bnx2x {scalar_t__ state; int /*<<< orphan*/  dev; scalar_t__ panic; } ;

/* Variables and functions */
 scalar_t__ BNX2X_STATE_OPEN ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ MAX_DESC_PER_TX_PKT ; 
 int /*<<< orphan*/  NETIF_MSG_TX_DONE ; 
 scalar_t__ TX_BD (scalar_t__) ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 scalar_t__ bnx2x_free_tx_pkt (struct bnx2x*,struct bnx2x_fp_txdata*,scalar_t__,unsigned int*,unsigned int*) ; 
 scalar_t__ bnx2x_tx_avail (struct bnx2x*,struct bnx2x_fp_txdata*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,unsigned int,unsigned int) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (scalar_t__) ; 

int bnx2x_tx_int(struct bnx2x *bp, struct bnx2x_fp_txdata *txdata)
{
	struct netdev_queue *txq;
	u16 hw_cons, sw_cons, bd_cons = txdata->tx_bd_cons;
	unsigned int pkts_compl = 0, bytes_compl = 0;

#ifdef BNX2X_STOP_ON_ERROR
	if (unlikely(bp->panic))
		return -1;
#endif

	txq = netdev_get_tx_queue(bp->dev, txdata->txq_index);
	hw_cons = le16_to_cpu(*txdata->tx_cons_sb);
	sw_cons = txdata->tx_pkt_cons;

	/* Ensure subsequent loads occur after hw_cons */
	smp_rmb();

	while (sw_cons != hw_cons) {
		u16 pkt_cons;

		pkt_cons = TX_BD(sw_cons);

		DP(NETIF_MSG_TX_DONE,
		   "queue[%d]: hw_cons %u  sw_cons %u  pkt_cons %u\n",
		   txdata->txq_index, hw_cons, sw_cons, pkt_cons);

		bd_cons = bnx2x_free_tx_pkt(bp, txdata, pkt_cons,
					    &pkts_compl, &bytes_compl);

		sw_cons++;
	}

	netdev_tx_completed_queue(txq, pkts_compl, bytes_compl);

	txdata->tx_pkt_cons = sw_cons;
	txdata->tx_bd_cons = bd_cons;

	/* Need to make the tx_bd_cons update visible to start_xmit()
	 * before checking for netif_tx_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that
	 * start_xmit() will miss it and cause the queue to be stopped
	 * forever.
	 * On the other hand we need an rmb() here to ensure the proper
	 * ordering of bit testing in the following
	 * netif_tx_queue_stopped(txq) call.
	 */
	smp_mb();

	if (unlikely(netif_tx_queue_stopped(txq))) {
		/* Taking tx_lock() is needed to prevent re-enabling the queue
		 * while it's empty. This could have happen if rx_action() gets
		 * suspended in bnx2x_tx_int() after the condition before
		 * netif_tx_wake_queue(), while tx_action (bnx2x_start_xmit()):
		 *
		 * stops the queue->sees fresh tx_bd_cons->releases the queue->
		 * sends some packets consuming the whole queue again->
		 * stops the queue
		 */

		__netif_tx_lock(txq, smp_processor_id());

		if ((netif_tx_queue_stopped(txq)) &&
		    (bp->state == BNX2X_STATE_OPEN) &&
		    (bnx2x_tx_avail(bp, txdata) >= MAX_DESC_PER_TX_PKT))
			netif_tx_wake_queue(txq);

		__netif_tx_unlock(txq);
	}
	return 0;
}