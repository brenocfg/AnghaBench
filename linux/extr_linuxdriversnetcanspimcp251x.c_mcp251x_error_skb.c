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
struct net_device {int dummy; } ;
struct can_frame {int can_id; int* data; } ;

/* Variables and functions */
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 

__attribute__((used)) static void mcp251x_error_skb(struct net_device *net, int can_id, int data1)
{
	struct sk_buff *skb;
	struct can_frame *frame;

	skb = alloc_can_err_skb(net, &frame);
	if (skb) {
		frame->can_id |= can_id;
		frame->data[1] = data1;
		netif_rx_ni(skb);
	} else {
		netdev_err(net, "cannot allocate error skb\n");
	}
}