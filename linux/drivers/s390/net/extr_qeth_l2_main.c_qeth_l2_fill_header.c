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
struct vlan_ethhdr {scalar_t__ h_vlan_proto; int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {scalar_t__ ip_summed; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_3__ {unsigned int pkt_length; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/ * flags; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ l2; } ;
struct qeth_hdr {TYPE_2__ hdr; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  QETH_HEADER_TYPE_L2_TSO ; 
 int /*<<< orphan*/  QETH_HEADER_TYPE_LAYER2 ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_BROADCAST ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_MULTICAST ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_UNICAST ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_VLAN ; 
 int RTN_BROADCAST ; 
 int RTN_MULTICAST ; 
 scalar_t__ __constant_htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int qeth_get_ether_cast_type (struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_tx_csum (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 struct vlan_ethhdr* vlan_eth_hdr (struct sk_buff*) ; 

__attribute__((used)) static void qeth_l2_fill_header(struct qeth_qdio_out_q *queue,
				struct qeth_hdr *hdr, struct sk_buff *skb,
				int ipv, unsigned int data_len)
{
	int cast_type = qeth_get_ether_cast_type(skb);
	struct vlan_ethhdr *veth = vlan_eth_hdr(skb);

	hdr->hdr.l2.pkt_length = data_len;

	if (skb_is_gso(skb)) {
		hdr->hdr.l2.id = QETH_HEADER_TYPE_L2_TSO;
	} else {
		hdr->hdr.l2.id = QETH_HEADER_TYPE_LAYER2;
		if (skb->ip_summed == CHECKSUM_PARTIAL)
			qeth_tx_csum(skb, &hdr->hdr.l2.flags[1], ipv);
	}

	/* set byte byte 3 to casting flags */
	if (cast_type == RTN_MULTICAST)
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_MULTICAST;
	else if (cast_type == RTN_BROADCAST)
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_BROADCAST;
	else
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_UNICAST;

	/* VSWITCH relies on the VLAN
	 * information to be present in
	 * the QDIO header */
	if (veth->h_vlan_proto == __constant_htons(ETH_P_8021Q)) {
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_VLAN;
		hdr->hdr.l2.vlan_id = ntohs(veth->h_vlan_TCI);
	}
}