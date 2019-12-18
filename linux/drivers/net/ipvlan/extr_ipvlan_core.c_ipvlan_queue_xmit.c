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
struct ipvl_port {int mode; } ;
struct ipvl_dev {int /*<<< orphan*/  phy_dev; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
#define  IPVLAN_MODE_L2 130 
#define  IPVLAN_MODE_L3 129 
#define  IPVLAN_MODE_L3S 128 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 struct ipvl_port* ipvlan_port_get_rcu_bh (int /*<<< orphan*/ ) ; 
 int ipvlan_xmit_mode_l2 (struct sk_buff*,struct net_device*) ; 
 int ipvlan_xmit_mode_l3 (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

int ipvlan_queue_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct ipvl_port *port = ipvlan_port_get_rcu_bh(ipvlan->phy_dev);

	if (!port)
		goto out;

	if (unlikely(!pskb_may_pull(skb, sizeof(struct ethhdr))))
		goto out;

	switch(port->mode) {
	case IPVLAN_MODE_L2:
		return ipvlan_xmit_mode_l2(skb, dev);
	case IPVLAN_MODE_L3:
#ifdef CONFIG_IPVLAN_L3S
	case IPVLAN_MODE_L3S:
#endif
		return ipvlan_xmit_mode_l3(skb, dev);
	}

	/* Should not reach here */
	WARN_ONCE(true, "ipvlan_queue_xmit() called for mode = [%hx]\n",
			  port->mode);
out:
	kfree_skb(skb);
	return NET_XMIT_DROP;
}