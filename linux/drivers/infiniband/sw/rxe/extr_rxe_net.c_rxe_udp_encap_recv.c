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
typedef  int /*<<< orphan*/  u8 ;
struct udphdr {int /*<<< orphan*/  len; } ;
struct sock {int dummy; } ;
struct sk_buff {struct net_device* dev; } ;
struct rxe_pkt_info {int port_num; scalar_t__ paylen; int /*<<< orphan*/  mask; int /*<<< orphan*/ * hdr; struct rxe_dev* rxe; } ;
struct rxe_dev {int /*<<< orphan*/  ib_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXE_GRH_MASK ; 
 struct rxe_pkt_info* SKB_TO_PKT (struct sk_buff*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_device_put (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rxe_dev* rxe_get_dev_from_net (struct net_device*) ; 
 int /*<<< orphan*/  rxe_rcv (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static int rxe_udp_encap_recv(struct sock *sk, struct sk_buff *skb)
{
	struct udphdr *udph;
	struct net_device *ndev = skb->dev;
	struct net_device *rdev = ndev;
	struct rxe_dev *rxe = rxe_get_dev_from_net(ndev);
	struct rxe_pkt_info *pkt = SKB_TO_PKT(skb);

	if (!rxe && is_vlan_dev(rdev)) {
		rdev = vlan_dev_real_dev(ndev);
		rxe = rxe_get_dev_from_net(rdev);
	}
	if (!rxe)
		goto drop;

	if (skb_linearize(skb)) {
		pr_err("skb_linearize failed\n");
		ib_device_put(&rxe->ib_dev);
		goto drop;
	}

	udph = udp_hdr(skb);
	pkt->rxe = rxe;
	pkt->port_num = 1;
	pkt->hdr = (u8 *)(udph + 1);
	pkt->mask = RXE_GRH_MASK;
	pkt->paylen = be16_to_cpu(udph->len) - sizeof(*udph);

	rxe_rcv(skb);

	/*
	 * FIXME: this is in the wrong place, it needs to be done when pkt is
	 * destroyed
	 */
	ib_device_put(&rxe->ib_dev);

	return 0;
drop:
	kfree_skb(skb);

	return 0;
}