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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct htt_tx_done {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ath10k_htt {TYPE_2__ tx_fetch_ind_q; int /*<<< orphan*/  txdone_fifo; int /*<<< orphan*/  num_mpdus_ready; TYPE_1__ rx_ring; int /*<<< orphan*/  rx_in_ord_compl_q; } ;
struct ath10k {struct ath10k_htt htt; } ;

/* Variables and functions */
 int EIO ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int ath10k_htt_rx_deliver_msdu (struct ath10k*,int,int) ; 
 int ath10k_htt_rx_handle_amsdu (struct ath10k_htt*) ; 
 int ath10k_htt_rx_in_ord_ind (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_htt_rx_msdu_buff_replenish (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_rx_tx_fetch_ind (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_mac_tx_push_pending (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_txrx_tx_unref (struct ath10k_htt*,struct htt_tx_done*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ kfifo_get (int /*<<< orphan*/ *,struct htt_tx_done*) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_splice_init (TYPE_2__*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ath10k_htt_txrx_compl_task(struct ath10k *ar, int budget)
{
	struct ath10k_htt *htt = &ar->htt;
	struct htt_tx_done tx_done = {};
	struct sk_buff_head tx_ind_q;
	struct sk_buff *skb;
	unsigned long flags;
	int quota = 0, done, ret;
	bool resched_napi = false;

	__skb_queue_head_init(&tx_ind_q);

	/* Process pending frames before dequeuing more data
	 * from hardware.
	 */
	quota = ath10k_htt_rx_deliver_msdu(ar, quota, budget);
	if (quota == budget) {
		resched_napi = true;
		goto exit;
	}

	while ((skb = skb_dequeue(&htt->rx_in_ord_compl_q))) {
		spin_lock_bh(&htt->rx_ring.lock);
		ret = ath10k_htt_rx_in_ord_ind(ar, skb);
		spin_unlock_bh(&htt->rx_ring.lock);

		dev_kfree_skb_any(skb);
		if (ret == -EIO) {
			resched_napi = true;
			goto exit;
		}
	}

	while (atomic_read(&htt->num_mpdus_ready)) {
		ret = ath10k_htt_rx_handle_amsdu(htt);
		if (ret == -EIO) {
			resched_napi = true;
			goto exit;
		}
		atomic_dec(&htt->num_mpdus_ready);
	}

	/* Deliver received data after processing data from hardware */
	quota = ath10k_htt_rx_deliver_msdu(ar, quota, budget);

	/* From NAPI documentation:
	 *  The napi poll() function may also process TX completions, in which
	 *  case if it processes the entire TX ring then it should count that
	 *  work as the rest of the budget.
	 */
	if ((quota < budget) && !kfifo_is_empty(&htt->txdone_fifo))
		quota = budget;

	/* kfifo_get: called only within txrx_tasklet so it's neatly serialized.
	 * From kfifo_get() documentation:
	 *  Note that with only one concurrent reader and one concurrent writer,
	 *  you don't need extra locking to use these macro.
	 */
	while (kfifo_get(&htt->txdone_fifo, &tx_done))
		ath10k_txrx_tx_unref(htt, &tx_done);

	ath10k_mac_tx_push_pending(ar);

	spin_lock_irqsave(&htt->tx_fetch_ind_q.lock, flags);
	skb_queue_splice_init(&htt->tx_fetch_ind_q, &tx_ind_q);
	spin_unlock_irqrestore(&htt->tx_fetch_ind_q.lock, flags);

	while ((skb = __skb_dequeue(&tx_ind_q))) {
		ath10k_htt_rx_tx_fetch_ind(ar, skb);
		dev_kfree_skb_any(skb);
	}

exit:
	ath10k_htt_rx_msdu_buff_replenish(htt);
	/* In case of rx failure or more data to read, report budget
	 * to reschedule NAPI poll
	 */
	done = resched_napi ? budget : quota;

	return done;
}