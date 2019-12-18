#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vlan_ethhdr {scalar_t__ h_vlan_proto; int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ ip_summed; } ;
struct rtable {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * s6_addr32; scalar_t__* s6_addr16; } ;
struct rt6_info {TYPE_6__ rt6i_gateway; } ;
struct qeth_qdio_out_q {struct qeth_card* card; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_6__ ipv6_addr; TYPE_1__ ipv4; } ;
struct qeth_hdr_layer3 {unsigned int length; int flags; TYPE_2__ next_hop; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  ext_flags; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {struct qeth_hdr_layer3 l3; } ;
struct qeth_hdr {TYPE_3__ hdr; } ;
struct qeth_card {int dummy; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_14__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_12__ {TYPE_6__ daddr; } ;
struct TYPE_11__ {int /*<<< orphan*/  destUserID; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int ETH_P_8021Q ; 
 int ETH_P_AF_IUCV ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int QETH_CAST_UNICAST ; 
 int /*<<< orphan*/  QETH_HDR_EXT_CSUM_HDR_REQ ; 
 int /*<<< orphan*/  QETH_HDR_EXT_INCLUDE_VLAN_TAG ; 
 int /*<<< orphan*/  QETH_HDR_EXT_VLAN_FRAME ; 
 int QETH_HDR_IPV6 ; 
 int QETH_HDR_PASSTHRU ; 
 int /*<<< orphan*/  QETH_HEADER_TYPE_L3_TSO ; 
 int /*<<< orphan*/  QETH_HEADER_TYPE_LAYER3 ; 
 scalar_t__ QETH_IQD_MCAST_TXQ ; 
 int RTN_UNICAST ; 
 scalar_t__ htons (int) ; 
 TYPE_7__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_any (TYPE_6__*) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 TYPE_4__* iucv_trans_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct dst_entry* qeth_dst_check_rcu (struct sk_buff*,int) ; 
 int qeth_l3_cast_type_to_flag (int) ; 
 int qeth_l3_get_cast_type_rcu (struct sk_buff*,struct dst_entry*,int) ; 
 int /*<<< orphan*/  qeth_tx_csum (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rt_nexthop (struct rtable*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 struct vlan_ethhdr* vlan_eth_hdr (struct sk_buff*) ; 

__attribute__((used)) static void qeth_l3_fill_header(struct qeth_qdio_out_q *queue,
				struct qeth_hdr *hdr, struct sk_buff *skb,
				int ipv, unsigned int data_len)
{
	struct qeth_hdr_layer3 *l3_hdr = &hdr->hdr.l3;
	struct vlan_ethhdr *veth = vlan_eth_hdr(skb);
	struct qeth_card *card = queue->card;
	struct dst_entry *dst;
	int cast_type;

	hdr->hdr.l3.length = data_len;

	if (skb_is_gso(skb)) {
		hdr->hdr.l3.id = QETH_HEADER_TYPE_L3_TSO;
	} else {
		hdr->hdr.l3.id = QETH_HEADER_TYPE_LAYER3;

		if (skb->protocol == htons(ETH_P_AF_IUCV)) {
			l3_hdr->flags = QETH_HDR_IPV6 | QETH_CAST_UNICAST;
			l3_hdr->next_hop.ipv6_addr.s6_addr16[0] = htons(0xfe80);
			memcpy(&l3_hdr->next_hop.ipv6_addr.s6_addr32[2],
			       iucv_trans_hdr(skb)->destUserID, 8);
			return;
		}

		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			qeth_tx_csum(skb, &hdr->hdr.l3.ext_flags, ipv);
			/* some HW requires combined L3+L4 csum offload: */
			if (ipv == 4)
				hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_CSUM_HDR_REQ;
		}
	}

	if (ipv == 4 || IS_IQD(card)) {
		/* NETIF_F_HW_VLAN_CTAG_TX */
		if (skb_vlan_tag_present(skb)) {
			hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_VLAN_FRAME;
			hdr->hdr.l3.vlan_id = skb_vlan_tag_get(skb);
		}
	} else if (veth->h_vlan_proto == htons(ETH_P_8021Q)) {
		hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_INCLUDE_VLAN_TAG;
		hdr->hdr.l3.vlan_id = ntohs(veth->h_vlan_TCI);
	}

	rcu_read_lock();
	dst = qeth_dst_check_rcu(skb, ipv);

	if (IS_IQD(card) && skb_get_queue_mapping(skb) != QETH_IQD_MCAST_TXQ)
		cast_type = RTN_UNICAST;
	else
		cast_type = qeth_l3_get_cast_type_rcu(skb, dst, ipv);
	l3_hdr->flags |= qeth_l3_cast_type_to_flag(cast_type);

	if (ipv == 4) {
		struct rtable *rt = (struct rtable *) dst;

		*((__be32 *) &hdr->hdr.l3.next_hop.ipv4.addr) = (rt) ?
				rt_nexthop(rt, ip_hdr(skb)->daddr) :
				ip_hdr(skb)->daddr;
	} else if (ipv == 6) {
		struct rt6_info *rt = (struct rt6_info *) dst;

		if (rt && !ipv6_addr_any(&rt->rt6i_gateway))
			l3_hdr->next_hop.ipv6_addr = rt->rt6i_gateway;
		else
			l3_hdr->next_hop.ipv6_addr = ipv6_hdr(skb)->daddr;

		hdr->hdr.l3.flags |= QETH_HDR_IPV6;
		if (!IS_IQD(card))
			hdr->hdr.l3.flags |= QETH_HDR_PASSTHRU;
	} else {
		/* OSA only: */
		l3_hdr->flags |= QETH_HDR_PASSTHRU;
	}
	rcu_read_unlock();
}