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
struct uml_net_private {int (* read ) (int /*<<< orphan*/ ,struct sk_buff*,struct uml_net_private*) ;int /*<<< orphan*/  (* protocol ) (struct sk_buff*) ;int /*<<< orphan*/  fd; int /*<<< orphan*/  max_packet; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 struct sk_buff* drop_skb ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct uml_net_private*) ; 
 int stub2 (int /*<<< orphan*/ ,struct sk_buff*,struct uml_net_private*) ; 
 int /*<<< orphan*/  stub3 (struct sk_buff*) ; 

__attribute__((used)) static int uml_net_rx(struct net_device *dev)
{
	struct uml_net_private *lp = netdev_priv(dev);
	int pkt_len;
	struct sk_buff *skb;

	/* If we can't allocate memory, try again next round. */
	skb = dev_alloc_skb(lp->max_packet);
	if (skb == NULL) {
		drop_skb->dev = dev;
		/* Read a packet into drop_skb and don't do anything with it. */
		(*lp->read)(lp->fd, drop_skb, lp);
		dev->stats.rx_dropped++;
		return 0;
	}

	skb->dev = dev;
	skb_put(skb, lp->max_packet);
	skb_reset_mac_header(skb);
	pkt_len = (*lp->read)(lp->fd, skb, lp);

	if (pkt_len > 0) {
		skb_trim(skb, pkt_len);
		skb->protocol = (*lp->protocol)(skb);

		dev->stats.rx_bytes += skb->len;
		dev->stats.rx_packets++;
		netif_rx(skb);
		return pkt_len;
	}

	kfree_skb(skb);
	return pkt_len;
}