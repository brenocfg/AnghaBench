#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; } ;
struct qmimux_priv {int /*<<< orphan*/  stats64; int /*<<< orphan*/  real_dev; int /*<<< orphan*/  mux_id; } ;
struct qmimux_hdr {int /*<<< orphan*/  pkt_len; int /*<<< orphan*/  mux_id; scalar_t__ pad; } ;
struct pcpu_sw_netstats {unsigned int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  scalar_t__ netdev_tx_t ;

/* Variables and functions */
 scalar_t__ NET_XMIT_CN ; 
 scalar_t__ NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 scalar_t__ dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct qmimux_priv* netdev_priv (struct net_device*) ; 
 struct qmimux_hdr* skb_push (struct sk_buff*,int) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t qmimux_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct qmimux_priv *priv = netdev_priv(dev);
	unsigned int len = skb->len;
	struct qmimux_hdr *hdr;
	netdev_tx_t ret;

	hdr = skb_push(skb, sizeof(struct qmimux_hdr));
	hdr->pad = 0;
	hdr->mux_id = priv->mux_id;
	hdr->pkt_len = cpu_to_be16(len);
	skb->dev = priv->real_dev;
	ret = dev_queue_xmit(skb);

	if (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) {
		struct pcpu_sw_netstats *stats64 = this_cpu_ptr(priv->stats64);

		u64_stats_update_begin(&stats64->syncp);
		stats64->tx_packets++;
		stats64->tx_bytes += len;
		u64_stats_update_end(&stats64->syncp);
	} else {
		dev->stats.tx_dropped++;
	}

	return ret;
}