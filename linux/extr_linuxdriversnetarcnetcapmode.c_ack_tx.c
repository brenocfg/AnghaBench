#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * proto; struct sk_buff* skb; } ;
struct arcnet_local {TYPE_4__ outgoing; } ;
struct TYPE_5__ {int ack; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cookie; TYPE_1__ mes; scalar_t__ proto; } ;
struct TYPE_7__ {TYPE_2__ cap; } ;
struct archdr {TYPE_3__ soft; } ;
struct arc_cap {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARC_HDR_SIZE ; 
 scalar_t__ BUGLVL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  D_PROTO ; 
 int /*<<< orphan*/  D_SKB ; 
 int /*<<< orphan*/  ETH_P_ARCNET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  arcnet_dump_skb (struct net_device*,struct sk_buff*,char*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,struct archdr*,scalar_t__) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int ack_tx(struct net_device *dev, int acked)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct sk_buff *ackskb;
	struct archdr *ackpkt;
	int length = sizeof(struct arc_cap);

	arc_printk(D_DURING, dev, "capmode: ack_tx: protocol: %x: result: %d\n",
		   lp->outgoing.skb->protocol, acked);

	if (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, lp->outgoing.skb, "ack_tx");

	/* Now alloc a skb to send back up through the layers: */
	ackskb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
	if (!ackskb)
		goto free_outskb;

	skb_put(ackskb, length + ARC_HDR_SIZE);
	ackskb->dev = dev;

	skb_reset_mac_header(ackskb);
	ackpkt = (struct archdr *)skb_mac_header(ackskb);
	/* skb_pull(ackskb, ARC_HDR_SIZE); */

	skb_copy_from_linear_data(lp->outgoing.skb, ackpkt,
				  ARC_HDR_SIZE + sizeof(struct arc_cap));
	ackpkt->soft.cap.proto = 0; /* using protocol 0 for acknowledge */
	ackpkt->soft.cap.mes.ack = acked;

	arc_printk(D_PROTO, dev, "Acknowledge for cap packet %x.\n",
		   *((int *)&ackpkt->soft.cap.cookie[0]));

	ackskb->protocol = cpu_to_be16(ETH_P_ARCNET);

	if (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, ackskb, "ack_tx_recv");
	netif_rx(ackskb);

free_outskb:
	dev_kfree_skb_irq(lp->outgoing.skb);
	lp->outgoing.proto = NULL;
			/* We are always finished when in this protocol */

	return 0;
}