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
struct sk_buff {struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ LAPB_OK ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ lapb_data_received (struct net_device*,struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x25_rx(struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;

	if ((skb = skb_share_check(skb, GFP_ATOMIC)) == NULL) {
		dev->stats.rx_dropped++;
		return NET_RX_DROP;
	}

	if (lapb_data_received(dev, skb) == LAPB_OK)
		return NET_RX_SUCCESS;

	dev->stats.rx_errors++;
	dev_kfree_skb_any(skb);
	return NET_RX_DROP;
}