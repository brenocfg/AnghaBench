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
struct lan743x_ptp {size_t tx_ts_skb_queue_size; int /*<<< orphan*/  tx_ts_lock; int /*<<< orphan*/  tx_ts_ignore_sync_queue; struct sk_buff** tx_ts_skb_queue; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; struct lan743x_ptp ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 size_t LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan743x_ptp_tx_ts_enqueue_skb(struct lan743x_adapter *adapter,
					  struct sk_buff *skb, bool ignore_sync)
{
	struct lan743x_ptp *ptp = &adapter->ptp;

	spin_lock_bh(&ptp->tx_ts_lock);
	if (ptp->tx_ts_skb_queue_size < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS) {
		ptp->tx_ts_skb_queue[ptp->tx_ts_skb_queue_size] = skb;
		if (ignore_sync)
			ptp->tx_ts_ignore_sync_queue |=
				BIT(ptp->tx_ts_skb_queue_size);
		ptp->tx_ts_skb_queue_size++;
	} else {
		/* this should never happen, so long as the tx channel
		 * calls and honors the result from
		 * lan743x_ptp_request_tx_timestamp
		 */
		netif_err(adapter, drv, adapter->netdev,
			  "tx ts skb queue overflow\n");
		dev_kfree_skb(skb);
	}
	spin_unlock_bh(&ptp->tx_ts_lock);
}