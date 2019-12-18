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
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  protocol; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 

__attribute__((used)) static void ath6kl_deliver_frames_to_nw_stack(struct net_device *dev,
					      struct sk_buff *skb)
{
	if (!skb)
		return;

	skb->dev = dev;

	if (!(skb->dev->flags & IFF_UP)) {
		dev_kfree_skb(skb);
		return;
	}

	skb->protocol = eth_type_trans(skb, skb->dev);

	netif_rx_ni(skb);
}