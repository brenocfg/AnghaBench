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
struct net_device_stats {int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int /*<<< orphan*/ * data; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_OVERFLOW ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int m_can_handle_lost_msg(struct net_device *dev)
{
	struct net_device_stats *stats = &dev->stats;
	struct sk_buff *skb;
	struct can_frame *frame;

	netdev_err(dev, "msg lost in rxf0\n");

	stats->rx_errors++;
	stats->rx_over_errors++;

	skb = alloc_can_err_skb(dev, &frame);
	if (unlikely(!skb))
		return 0;

	frame->can_id |= CAN_ERR_CRTL;
	frame->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	netif_receive_skb(skb);

	return 1;
}