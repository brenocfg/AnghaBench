#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {scalar_t__ mtu; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_3__ {scalar_t__ (* poll ) (struct iss_net_private*) ;int (* read ) (struct iss_net_private*,struct sk_buff**) ;int /*<<< orphan*/  (* protocol ) (struct sk_buff*) ;} ;
struct iss_net_private {TYPE_2__ stats; TYPE_1__ tp; } ;

/* Variables and functions */
 scalar_t__ ETH_HEADER_OTHER ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct iss_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ stub1 (struct iss_net_private*) ; 
 int stub2 (struct iss_net_private*,struct sk_buff**) ; 
 int /*<<< orphan*/  stub3 (struct sk_buff*) ; 

__attribute__((used)) static int iss_net_rx(struct net_device *dev)
{
	struct iss_net_private *lp = netdev_priv(dev);
	int pkt_len;
	struct sk_buff *skb;

	/* Check if there is any new data. */

	if (lp->tp.poll(lp) == 0)
		return 0;

	/* Try to allocate memory, if it fails, try again next round. */

	skb = dev_alloc_skb(dev->mtu + 2 + ETH_HEADER_OTHER);
	if (skb == NULL) {
		lp->stats.rx_dropped++;
		return 0;
	}

	skb_reserve(skb, 2);

	/* Setup skb */

	skb->dev = dev;
	skb_reset_mac_header(skb);
	pkt_len = lp->tp.read(lp, &skb);
	skb_put(skb, pkt_len);

	if (pkt_len > 0) {
		skb_trim(skb, pkt_len);
		skb->protocol = lp->tp.protocol(skb);

		lp->stats.rx_bytes += skb->len;
		lp->stats.rx_packets++;
		netif_rx_ni(skb);
		return pkt_len;
	}
	kfree_skb(skb);
	return pkt_len;
}