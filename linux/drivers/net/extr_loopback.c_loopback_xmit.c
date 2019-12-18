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
struct sk_buff {int len; int /*<<< orphan*/  protocol; scalar_t__ tstamp; } ;
struct pcpu_lstats {int bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  packets; } ;
struct net_device {int /*<<< orphan*/  lstats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ NET_RX_SUCCESS ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_force (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 struct pcpu_lstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t loopback_xmit(struct sk_buff *skb,
				 struct net_device *dev)
{
	struct pcpu_lstats *lb_stats;
	int len;

	skb_tx_timestamp(skb);

	/* do not fool net_timestamp_check() with various clock bases */
	skb->tstamp = 0;

	skb_orphan(skb);

	/* Before queueing this packet to netif_rx(),
	 * make sure dst is refcounted.
	 */
	skb_dst_force(skb);

	skb->protocol = eth_type_trans(skb, dev);

	/* it's OK to use per_cpu_ptr() because BHs are off */
	lb_stats = this_cpu_ptr(dev->lstats);

	len = skb->len;
	if (likely(netif_rx(skb) == NET_RX_SUCCESS)) {
		u64_stats_update_begin(&lb_stats->syncp);
		lb_stats->bytes += len;
		lb_stats->packets++;
		u64_stats_update_end(&lb_stats->syncp);
	}

	return NETDEV_TX_OK;
}