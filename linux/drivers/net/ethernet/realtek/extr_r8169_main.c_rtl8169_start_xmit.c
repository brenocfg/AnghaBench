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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rtl8169_private {unsigned int cur_tx; TYPE_3__* tx_skb; struct TxDesc* TxDescArray; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct device {int dummy; } ;
struct TxDesc {int /*<<< orphan*/  opts1; int /*<<< orphan*/  opts2; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int len; struct sk_buff* skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int DescOwn ; 
 int FirstFrag ; 
 int LastFrag ; 
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 unsigned int NUM_TX_DESC ; 
 int __netdev_sent_queue (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  drv ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ net_ratelimit () ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_doorbell (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_get_txd_opts1 (int,int,unsigned int) ; 
 int /*<<< orphan*/  rtl8169_tso_csum_v1 (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  rtl8169_tso_csum_v2 (struct rtl8169_private*,struct sk_buff*,int*) ; 
 int rtl8169_tx_vlan_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl8169_unmap_tx_skb (struct device*,TYPE_3__*,struct TxDesc*) ; 
 int rtl8169_xmit_frags (struct rtl8169_private*,struct sk_buff*,int*) ; 
 scalar_t__ rtl_chip_supports_csum_v2 (struct rtl8169_private*) ; 
 scalar_t__ rtl_tx_slots_avail (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t rtl8169_start_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	unsigned int entry = tp->cur_tx % NUM_TX_DESC;
	struct TxDesc *txd = tp->TxDescArray + entry;
	struct device *d = tp_to_dev(tp);
	dma_addr_t mapping;
	u32 opts[2], len;
	bool stop_queue;
	bool door_bell;
	int frags;

	if (unlikely(!rtl_tx_slots_avail(tp, skb_shinfo(skb)->nr_frags))) {
		netif_err(tp, drv, dev, "BUG! Tx Ring full when queue awake!\n");
		goto err_stop_0;
	}

	if (unlikely(le32_to_cpu(txd->opts1) & DescOwn))
		goto err_stop_0;

	opts[1] = rtl8169_tx_vlan_tag(skb);
	opts[0] = DescOwn;

	if (rtl_chip_supports_csum_v2(tp)) {
		if (!rtl8169_tso_csum_v2(tp, skb, opts))
			goto err_dma_0;
	} else {
		rtl8169_tso_csum_v1(skb, opts);
	}

	len = skb_headlen(skb);
	mapping = dma_map_single(d, skb->data, len, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(d, mapping))) {
		if (net_ratelimit())
			netif_err(tp, drv, dev, "Failed to map TX DMA!\n");
		goto err_dma_0;
	}

	tp->tx_skb[entry].len = len;
	txd->addr = cpu_to_le64(mapping);

	frags = rtl8169_xmit_frags(tp, skb, opts);
	if (frags < 0)
		goto err_dma_1;
	else if (frags)
		opts[0] |= FirstFrag;
	else {
		opts[0] |= FirstFrag | LastFrag;
		tp->tx_skb[entry].skb = skb;
	}

	txd->opts2 = cpu_to_le32(opts[1]);

	skb_tx_timestamp(skb);

	/* Force memory writes to complete before releasing descriptor */
	dma_wmb();

	door_bell = __netdev_sent_queue(dev, skb->len, netdev_xmit_more());

	txd->opts1 = rtl8169_get_txd_opts1(opts[0], len, entry);

	/* Force all memory writes to complete before notifying device */
	wmb();

	tp->cur_tx += frags + 1;

	stop_queue = !rtl_tx_slots_avail(tp, MAX_SKB_FRAGS);
	if (unlikely(stop_queue)) {
		/* Avoid wrongly optimistic queue wake-up: rtl_tx thread must
		 * not miss a ring update when it notices a stopped queue.
		 */
		smp_wmb();
		netif_stop_queue(dev);
		door_bell = true;
	}

	if (door_bell)
		rtl8169_doorbell(tp);

	if (unlikely(stop_queue)) {
		/* Sync with rtl_tx:
		 * - publish queue status and cur_tx ring index (write barrier)
		 * - refresh dirty_tx ring index (read barrier).
		 * May the current thread have a pessimistic view of the ring
		 * status and forget to wake up queue, a racing rtl_tx thread
		 * can't.
		 */
		smp_mb();
		if (rtl_tx_slots_avail(tp, MAX_SKB_FRAGS))
			netif_start_queue(dev);
	}

	return NETDEV_TX_OK;

err_dma_1:
	rtl8169_unmap_tx_skb(d, tp->tx_skb + entry, txd);
err_dma_0:
	dev_kfree_skb_any(skb);
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;

err_stop_0:
	netif_stop_queue(dev);
	dev->stats.tx_dropped++;
	return NETDEV_TX_BUSY;
}