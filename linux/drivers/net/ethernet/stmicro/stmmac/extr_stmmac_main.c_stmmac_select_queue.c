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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int real_num_tx_queues; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int netdev_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static u16 stmmac_select_queue(struct net_device *dev, struct sk_buff *skb,
			       struct net_device *sb_dev)
{
	if (skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) {
		/*
		 * There is no way to determine the number of TSO
		 * capable Queues. Let's use always the Queue 0
		 * because if TSO is supported then at least this
		 * one will be capable.
		 */
		return 0;
	}

	return netdev_pick_tx(dev, skb, NULL) % dev->real_num_tx_queues;
}