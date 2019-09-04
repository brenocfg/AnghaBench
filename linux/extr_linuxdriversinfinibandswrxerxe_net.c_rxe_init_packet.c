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
struct udphdr {int dummy; } ;
struct sk_buff {void* protocol; struct net_device* dev; } ;
struct rxe_pkt_info {int port_num; int /*<<< orphan*/  mask; int /*<<< orphan*/  hdr; struct rxe_dev* rxe; } ;
struct rxe_dev {struct net_device* ndev; int /*<<< orphan*/  ib_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgid_index; } ;
struct rxe_av {scalar_t__ network_type; TYPE_1__ grh; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct ib_gid_attr {struct net_device* ndev; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct ib_gid_attr const*) ; 
 scalar_t__ LL_RESERVED_SPACE (struct net_device*) ; 
 scalar_t__ RDMA_NETWORK_IPV4 ; 
 int /*<<< orphan*/  RXE_GRH_MASK ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct ib_gid_attr* rdma_get_gid_attr (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *rxe_init_packet(struct rxe_dev *rxe, struct rxe_av *av,
				int paylen, struct rxe_pkt_info *pkt)
{
	unsigned int hdr_len;
	struct sk_buff *skb;
	struct net_device *ndev;
	const struct ib_gid_attr *attr;
	const int port_num = 1;

	attr = rdma_get_gid_attr(&rxe->ib_dev, port_num, av->grh.sgid_index);
	if (IS_ERR(attr))
		return NULL;
	ndev = attr->ndev;

	if (av->network_type == RDMA_NETWORK_IPV4)
		hdr_len = ETH_HLEN + sizeof(struct udphdr) +
			sizeof(struct iphdr);
	else
		hdr_len = ETH_HLEN + sizeof(struct udphdr) +
			sizeof(struct ipv6hdr);

	skb = alloc_skb(paylen + hdr_len + LL_RESERVED_SPACE(ndev),
			GFP_ATOMIC);

	if (unlikely(!skb))
		goto out;

	skb_reserve(skb, hdr_len + LL_RESERVED_SPACE(rxe->ndev));

	skb->dev	= ndev;
	if (av->network_type == RDMA_NETWORK_IPV4)
		skb->protocol = htons(ETH_P_IP);
	else
		skb->protocol = htons(ETH_P_IPV6);

	pkt->rxe	= rxe;
	pkt->port_num	= port_num;
	pkt->hdr	= skb_put_zero(skb, paylen);
	pkt->mask	|= RXE_GRH_MASK;

out:
	rdma_put_gid_attr(attr);
	return skb;
}