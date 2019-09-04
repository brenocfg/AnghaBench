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
struct sk_buff {int /*<<< orphan*/  ip_summed; struct net_device* dev; int /*<<< orphan*/  pkt_type; scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct canfd_frame {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 

__attribute__((used)) static void vcan_rx(struct sk_buff *skb, struct net_device *dev)
{
	struct canfd_frame *cfd = (struct canfd_frame *)skb->data;
	struct net_device_stats *stats = &dev->stats;

	stats->rx_packets++;
	stats->rx_bytes += cfd->len;

	skb->pkt_type  = PACKET_BROADCAST;
	skb->dev       = dev;
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	netif_rx_ni(skb);
}