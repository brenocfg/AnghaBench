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
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct mtk_tx_ring {int thresh; int /*<<< orphan*/  free_count; } ;
struct mtk_mac {struct mtk_eth* hw; } ;
struct mtk_eth {int /*<<< orphan*/  page_lock; int /*<<< orphan*/  state; struct mtk_tx_ring tx_ring; } ;
struct TYPE_4__ {int gso_type; int /*<<< orphan*/  gso_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  check; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_RESETTING ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int mtk_cal_txd_req (struct sk_buff*) ; 
 int /*<<< orphan*/  mtk_stop_queue (struct mtk_eth*) ; 
 scalar_t__ mtk_tx_map (struct sk_buff*,struct net_device*,int,struct mtk_tx_ring*,int) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct mtk_eth*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_warn (struct mtk_eth*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  tx_queued ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtk_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;
	struct mtk_tx_ring *ring = &eth->tx_ring;
	struct net_device_stats *stats = &dev->stats;
	bool gso = false;
	int tx_num;

	/* normally we can rely on the stack not calling this more than once,
	 * however we have 2 queues running on the same ring so we need to lock
	 * the ring access
	 */
	spin_lock(&eth->page_lock);

	if (unlikely(test_bit(MTK_RESETTING, &eth->state)))
		goto drop;

	tx_num = mtk_cal_txd_req(skb);
	if (unlikely(atomic_read(&ring->free_count) <= tx_num)) {
		mtk_stop_queue(eth);
		netif_err(eth, tx_queued, dev,
			  "Tx Ring full when queue awake!\n");
		spin_unlock(&eth->page_lock);
		return NETDEV_TX_BUSY;
	}

	/* TSO: fill MSS info in tcp checksum field */
	if (skb_is_gso(skb)) {
		if (skb_cow_head(skb, 0)) {
			netif_warn(eth, tx_err, dev,
				   "GSO expand head fail.\n");
			goto drop;
		}

		if (skb_shinfo(skb)->gso_type &
				(SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) {
			gso = true;
			tcp_hdr(skb)->check = htons(skb_shinfo(skb)->gso_size);
		}
	}

	if (mtk_tx_map(skb, dev, tx_num, ring, gso) < 0)
		goto drop;

	if (unlikely(atomic_read(&ring->free_count) <= ring->thresh))
		mtk_stop_queue(eth);

	spin_unlock(&eth->page_lock);

	return NETDEV_TX_OK;

drop:
	spin_unlock(&eth->page_lock);
	stats->tx_dropped++;
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}