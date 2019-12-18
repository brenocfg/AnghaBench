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
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {scalar_t__ can_dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_RX ; 
 struct sk_buff* alloc_can_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  at91_read_mb (struct net_device*,unsigned int,struct can_frame*) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void at91_read_msg(struct net_device *dev, unsigned int mb)
{
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;

	skb = alloc_can_skb(dev, &cf);
	if (unlikely(!skb)) {
		stats->rx_dropped++;
		return;
	}

	at91_read_mb(dev, mb, cf);

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_receive_skb(skb);

	can_led_event(dev, CAN_LED_EVENT_RX);
}