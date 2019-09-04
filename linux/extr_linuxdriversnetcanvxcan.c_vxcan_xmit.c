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
struct vxcan_priv {int /*<<< orphan*/  peer; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; struct net_device* dev; int /*<<< orphan*/  pkt_type; scalar_t__ csum_start; scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct canfd_frame {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ NET_RX_SUCCESS ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 struct sk_buff* can_create_echo_skb (struct sk_buff*) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct vxcan_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_rx_ni (struct sk_buff*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t vxcan_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct vxcan_priv *priv = netdev_priv(dev);
	struct net_device *peer;
	struct canfd_frame *cfd = (struct canfd_frame *)skb->data;
	struct net_device_stats *peerstats, *srcstats = &dev->stats;

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;

	rcu_read_lock();
	peer = rcu_dereference(priv->peer);
	if (unlikely(!peer)) {
		kfree_skb(skb);
		dev->stats.tx_dropped++;
		goto out_unlock;
	}

	skb = can_create_echo_skb(skb);
	if (!skb)
		goto out_unlock;

	/* reset CAN GW hop counter */
	skb->csum_start = 0;
	skb->pkt_type   = PACKET_BROADCAST;
	skb->dev        = peer;
	skb->ip_summed  = CHECKSUM_UNNECESSARY;

	if (netif_rx_ni(skb) == NET_RX_SUCCESS) {
		srcstats->tx_packets++;
		srcstats->tx_bytes += cfd->len;
		peerstats = &peer->stats;
		peerstats->rx_packets++;
		peerstats->rx_bytes += cfd->len;
	}

out_unlock:
	rcu_read_unlock();
	return NETDEV_TX_OK;
}