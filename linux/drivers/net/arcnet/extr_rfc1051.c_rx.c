#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ data; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* copy_from_card ) (struct net_device*,int,int,scalar_t__,int) ;} ;
struct arcnet_local {TYPE_2__ hw; } ;
struct TYPE_6__ {scalar_t__ raw; } ;
struct archdr {TYPE_3__ soft; } ;

/* Variables and functions */
 scalar_t__ ARC_HDR_SIZE ; 
 scalar_t__ BUGLVL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  D_SKB ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MinTU ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  arcnet_dump_skb (struct net_device*,struct sk_buff*,char*) ; 
 int /*<<< orphan*/  memcpy (struct archdr*,struct archdr*,int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  type_trans (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void rx(struct net_device *dev, int bufnum,
	       struct archdr *pkthdr, int length)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct sk_buff *skb;
	struct archdr *pkt = pkthdr;
	int ofs;

	arc_printk(D_DURING, dev, "it's a raw packet (length=%d)\n", length);

	if (length >= MinTU)
		ofs = 512 - length;
	else
		ofs = 256 - length;

	skb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
	if (!skb) {
		dev->stats.rx_dropped++;
		return;
	}
	skb_put(skb, length + ARC_HDR_SIZE);
	skb->dev = dev;

	pkt = (struct archdr *)skb->data;

	/* up to sizeof(pkt->soft) has already been copied from the card */
	memcpy(pkt, pkthdr, sizeof(struct archdr));
	if (length > sizeof(pkt->soft))
		lp->hw.copy_from_card(dev, bufnum, ofs + sizeof(pkt->soft),
				      pkt->soft.raw + sizeof(pkt->soft),
				      length - sizeof(pkt->soft));

	if (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, skb, "rx");

	skb->protocol = type_trans(skb, dev);
	netif_rx(skb);
}