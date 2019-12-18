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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct ipvl_dev {int /*<<< orphan*/  phy_dev; int /*<<< orphan*/  port; } ;
struct ipvl_addr {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int dev_forward_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipvl_addr* ipvlan_addr_lookup (int /*<<< orphan*/ ,void*,int,int) ; 
 void* ipvlan_get_L3_hdr (int /*<<< orphan*/ ,struct sk_buff*,int*) ; 
 scalar_t__ ipvlan_is_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipvlan_is_vepa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipvlan_multicast_enqueue (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int ipvlan_rcv_frame (struct ipvl_addr*,struct sk_buff**,int) ; 
 int /*<<< orphan*/  ipvlan_skb_crossing_ns (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipvlan_xmit_mode_l2(struct sk_buff *skb, struct net_device *dev)
{
	const struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct ethhdr *eth = eth_hdr(skb);
	struct ipvl_addr *addr;
	void *lyr3h;
	int addr_type;

	if (!ipvlan_is_vepa(ipvlan->port) &&
	    ether_addr_equal(eth->h_dest, eth->h_source)) {
		lyr3h = ipvlan_get_L3_hdr(ipvlan->port, skb, &addr_type);
		if (lyr3h) {
			addr = ipvlan_addr_lookup(ipvlan->port, lyr3h, addr_type, true);
			if (addr) {
				if (ipvlan_is_private(ipvlan->port)) {
					consume_skb(skb);
					return NET_XMIT_DROP;
				}
				return ipvlan_rcv_frame(addr, &skb, true);
			}
		}
		skb = skb_share_check(skb, GFP_ATOMIC);
		if (!skb)
			return NET_XMIT_DROP;

		/* Packet definitely does not belong to any of the
		 * virtual devices, but the dest is local. So forward
		 * the skb for the main-dev. At the RX side we just return
		 * RX_PASS for it to be processed further on the stack.
		 */
		return dev_forward_skb(ipvlan->phy_dev, skb);

	} else if (is_multicast_ether_addr(eth->h_dest)) {
		ipvlan_skb_crossing_ns(skb, NULL);
		ipvlan_multicast_enqueue(ipvlan->port, skb, true);
		return NET_XMIT_SUCCESS;
	}

	skb->dev = ipvlan->phy_dev;
	return dev_queue_xmit(skb);
}