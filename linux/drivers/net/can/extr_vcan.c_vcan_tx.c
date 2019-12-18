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
struct sk_buff {scalar_t__ pkt_type; scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct canfd_frame {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ PACKET_LOOPBACK ; 
 struct sk_buff* can_create_echo_skb (struct sk_buff*) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  echo ; 
 int /*<<< orphan*/  vcan_rx (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t vcan_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct canfd_frame *cfd = (struct canfd_frame *)skb->data;
	struct net_device_stats *stats = &dev->stats;
	int loop;

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;

	stats->tx_packets++;
	stats->tx_bytes += cfd->len;

	/* set flag whether this packet has to be looped back */
	loop = skb->pkt_type == PACKET_LOOPBACK;

	if (!echo) {
		/* no echo handling available inside this driver */
		if (loop) {
			/* only count the packets here, because the
			 * CAN core already did the echo for us
			 */
			stats->rx_packets++;
			stats->rx_bytes += cfd->len;
		}
		consume_skb(skb);
		return NETDEV_TX_OK;
	}

	/* perform standard echo handling for CAN network interfaces */

	if (loop) {
		skb = can_create_echo_skb(skb);
		if (!skb)
			return NETDEV_TX_OK;

		/* receive with packet counting */
		vcan_rx(skb, dev);
	} else {
		/* no looped packets => no counting */
		consume_skb(skb);
	}
	return NETDEV_TX_OK;
}