#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {unsigned int packets; unsigned int bytes; int /*<<< orphan*/  syncp; } ;
struct rtl8169_private {unsigned int dirty_tx; unsigned int cur_tx; TYPE_1__ tx_stats; TYPE_2__* TxDescArray; struct ring_info* tx_skb; } ;
struct ring_info {TYPE_3__* skb; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  opts1; } ;

/* Variables and functions */
 int DescOwn ; 
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 unsigned int NUM_TX_DESC ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_consume_skb (TYPE_3__*,int) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,unsigned int,unsigned int) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_doorbell (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_unmap_tx_skb (int /*<<< orphan*/ ,struct ring_info*,TYPE_2__*) ; 
 scalar_t__ rtl_tx_slots_avail (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  tp_to_dev (struct rtl8169_private*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl_tx(struct net_device *dev, struct rtl8169_private *tp,
		   int budget)
{
	unsigned int dirty_tx, tx_left, bytes_compl = 0, pkts_compl = 0;

	dirty_tx = tp->dirty_tx;
	smp_rmb();
	tx_left = tp->cur_tx - dirty_tx;

	while (tx_left > 0) {
		unsigned int entry = dirty_tx % NUM_TX_DESC;
		struct ring_info *tx_skb = tp->tx_skb + entry;
		u32 status;

		status = le32_to_cpu(tp->TxDescArray[entry].opts1);
		if (status & DescOwn)
			break;

		/* This barrier is needed to keep us from reading
		 * any other fields out of the Tx descriptor until
		 * we know the status of DescOwn
		 */
		dma_rmb();

		rtl8169_unmap_tx_skb(tp_to_dev(tp), tx_skb,
				     tp->TxDescArray + entry);
		if (tx_skb->skb) {
			pkts_compl++;
			bytes_compl += tx_skb->skb->len;
			napi_consume_skb(tx_skb->skb, budget);
			tx_skb->skb = NULL;
		}
		dirty_tx++;
		tx_left--;
	}

	if (tp->dirty_tx != dirty_tx) {
		netdev_completed_queue(dev, pkts_compl, bytes_compl);

		u64_stats_update_begin(&tp->tx_stats.syncp);
		tp->tx_stats.packets += pkts_compl;
		tp->tx_stats.bytes += bytes_compl;
		u64_stats_update_end(&tp->tx_stats.syncp);

		tp->dirty_tx = dirty_tx;
		/* Sync with rtl8169_start_xmit:
		 * - publish dirty_tx ring index (write barrier)
		 * - refresh cur_tx ring index and queue status (read barrier)
		 * May the current thread miss the stopped queue condition,
		 * a racing xmit thread can only have a right view of the
		 * ring status.
		 */
		smp_mb();
		if (netif_queue_stopped(dev) &&
		    rtl_tx_slots_avail(tp, MAX_SKB_FRAGS)) {
			netif_wake_queue(dev);
		}
		/*
		 * 8168 hack: TxPoll requests are lost when the Tx packets are
		 * too close. Let's kick an extra TxPoll request when a burst
		 * of start_xmit activity is detected (if it is not detected,
		 * it is slow enough). -- FR
		 */
		if (tp->cur_tx != dirty_tx)
			rtl8169_doorbell(tp);
	}
}