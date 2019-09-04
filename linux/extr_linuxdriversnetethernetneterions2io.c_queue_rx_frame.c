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
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_2__ {scalar_t__ napi; } ;
struct s2io_nic {TYPE_1__ config; scalar_t__ vlan_strip_flag; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void queue_rx_frame(struct sk_buff *skb, u16 vlan_tag)
{
	struct net_device *dev = skb->dev;
	struct s2io_nic *sp = netdev_priv(dev);

	skb->protocol = eth_type_trans(skb, dev);
	if (vlan_tag && sp->vlan_strip_flag)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
	if (sp->config.napi)
		netif_receive_skb(skb);
	else
		netif_rx(skb);
}