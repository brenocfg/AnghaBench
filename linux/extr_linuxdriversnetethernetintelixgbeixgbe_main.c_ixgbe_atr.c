#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int vlan_id; int /*<<< orphan*/  flow_type; } ;
struct TYPE_6__ {int src; int /*<<< orphan*/  dst; } ;
union ixgbe_atr_hash_dword {int ip; TYPE_4__ formatted; TYPE_1__ port; int /*<<< orphan*/  dword; } ;
struct tcphdr {int dest; int /*<<< orphan*/  source; int /*<<< orphan*/  syn; scalar_t__ fin; } ;
struct sk_buff {unsigned char* data; scalar_t__ encapsulation; } ;
struct ixgbe_tx_buffer {int protocol; int tx_flags; struct sk_buff* skb; } ;
struct ixgbe_ring {scalar_t__ atr_sample_rate; scalar_t__ atr_count; int /*<<< orphan*/  queue_index; struct ixgbe_q_vector* q_vector; } ;
struct ixgbe_q_vector {struct ixgbe_adapter* adapter; } ;
struct ixgbe_adapter {scalar_t__ vxlan_port; scalar_t__ geneve_port; int /*<<< orphan*/  hw; } ;
struct TYPE_8__ {int* s6_addr32; } ;
struct TYPE_7__ {int* s6_addr32; } ;
struct ipv6hdr {TYPE_3__ daddr; TYPE_2__ saddr; } ;
struct iphdr {scalar_t__ protocol; int version; int saddr; int daddr; } ;
typedef  int __be16 ;
struct TYPE_10__ {scalar_t__ dest; } ;

/* Variables and functions */
 int ETH_P_8021Q ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
#define  IPVERSION 128 
 int /*<<< orphan*/  IXGBE_ATR_FLOW_TYPE_TCPV4 ; 
 int /*<<< orphan*/  IXGBE_ATR_FLOW_TYPE_TCPV6 ; 
 int /*<<< orphan*/  IXGBE_ATR_L4TYPE_TUNNEL_MASK ; 
 int IXGBE_TX_FLAGS_HW_VLAN ; 
 int IXGBE_TX_FLAGS_SW_VLAN ; 
 int IXGBE_TX_FLAGS_VLAN_SHIFT ; 
 int VXLAN_HEADROOM ; 
 int htons (int) ; 
 int ipv6_find_hdr (struct sk_buff*,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_fdir_add_signature_filter_82599 (int /*<<< orphan*/ *,union ixgbe_atr_hash_dword,union ixgbe_atr_hash_dword,int /*<<< orphan*/ ) ; 
 void* skb_inner_network_header (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 TYPE_5__* udp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ixgbe_atr(struct ixgbe_ring *ring,
		      struct ixgbe_tx_buffer *first)
{
	struct ixgbe_q_vector *q_vector = ring->q_vector;
	union ixgbe_atr_hash_dword input = { .dword = 0 };
	union ixgbe_atr_hash_dword common = { .dword = 0 };
	union {
		unsigned char *network;
		struct iphdr *ipv4;
		struct ipv6hdr *ipv6;
	} hdr;
	struct tcphdr *th;
	unsigned int hlen;
	struct sk_buff *skb;
	__be16 vlan_id;
	int l4_proto;

	/* if ring doesn't have a interrupt vector, cannot perform ATR */
	if (!q_vector)
		return;

	/* do nothing if sampling is disabled */
	if (!ring->atr_sample_rate)
		return;

	ring->atr_count++;

	/* currently only IPv4/IPv6 with TCP is supported */
	if ((first->protocol != htons(ETH_P_IP)) &&
	    (first->protocol != htons(ETH_P_IPV6)))
		return;

	/* snag network header to get L4 type and address */
	skb = first->skb;
	hdr.network = skb_network_header(skb);
	if (unlikely(hdr.network <= skb->data))
		return;
	if (skb->encapsulation &&
	    first->protocol == htons(ETH_P_IP) &&
	    hdr.ipv4->protocol == IPPROTO_UDP) {
		struct ixgbe_adapter *adapter = q_vector->adapter;

		if (unlikely(skb_tail_pointer(skb) < hdr.network +
			     VXLAN_HEADROOM))
			return;

		/* verify the port is recognized as VXLAN */
		if (adapter->vxlan_port &&
		    udp_hdr(skb)->dest == adapter->vxlan_port)
			hdr.network = skb_inner_network_header(skb);

		if (adapter->geneve_port &&
		    udp_hdr(skb)->dest == adapter->geneve_port)
			hdr.network = skb_inner_network_header(skb);
	}

	/* Make sure we have at least [minimum IPv4 header + TCP]
	 * or [IPv6 header] bytes
	 */
	if (unlikely(skb_tail_pointer(skb) < hdr.network + 40))
		return;

	/* Currently only IPv4/IPv6 with TCP is supported */
	switch (hdr.ipv4->version) {
	case IPVERSION:
		/* access ihl as u8 to avoid unaligned access on ia64 */
		hlen = (hdr.network[0] & 0x0F) << 2;
		l4_proto = hdr.ipv4->protocol;
		break;
	case 6:
		hlen = hdr.network - skb->data;
		l4_proto = ipv6_find_hdr(skb, &hlen, IPPROTO_TCP, NULL, NULL);
		hlen -= hdr.network - skb->data;
		break;
	default:
		return;
	}

	if (l4_proto != IPPROTO_TCP)
		return;

	if (unlikely(skb_tail_pointer(skb) < hdr.network +
		     hlen + sizeof(struct tcphdr)))
		return;

	th = (struct tcphdr *)(hdr.network + hlen);

	/* skip this packet since the socket is closing */
	if (th->fin)
		return;

	/* sample on all syn packets or once every atr sample count */
	if (!th->syn && (ring->atr_count < ring->atr_sample_rate))
		return;

	/* reset sample count */
	ring->atr_count = 0;

	vlan_id = htons(first->tx_flags >> IXGBE_TX_FLAGS_VLAN_SHIFT);

	/*
	 * src and dst are inverted, think how the receiver sees them
	 *
	 * The input is broken into two sections, a non-compressed section
	 * containing vm_pool, vlan_id, and flow_type.  The rest of the data
	 * is XORed together and stored in the compressed dword.
	 */
	input.formatted.vlan_id = vlan_id;

	/*
	 * since src port and flex bytes occupy the same word XOR them together
	 * and write the value to source port portion of compressed dword
	 */
	if (first->tx_flags & (IXGBE_TX_FLAGS_SW_VLAN | IXGBE_TX_FLAGS_HW_VLAN))
		common.port.src ^= th->dest ^ htons(ETH_P_8021Q);
	else
		common.port.src ^= th->dest ^ first->protocol;
	common.port.dst ^= th->source;

	switch (hdr.ipv4->version) {
	case IPVERSION:
		input.formatted.flow_type = IXGBE_ATR_FLOW_TYPE_TCPV4;
		common.ip ^= hdr.ipv4->saddr ^ hdr.ipv4->daddr;
		break;
	case 6:
		input.formatted.flow_type = IXGBE_ATR_FLOW_TYPE_TCPV6;
		common.ip ^= hdr.ipv6->saddr.s6_addr32[0] ^
			     hdr.ipv6->saddr.s6_addr32[1] ^
			     hdr.ipv6->saddr.s6_addr32[2] ^
			     hdr.ipv6->saddr.s6_addr32[3] ^
			     hdr.ipv6->daddr.s6_addr32[0] ^
			     hdr.ipv6->daddr.s6_addr32[1] ^
			     hdr.ipv6->daddr.s6_addr32[2] ^
			     hdr.ipv6->daddr.s6_addr32[3];
		break;
	default:
		break;
	}

	if (hdr.network != skb_network_header(skb))
		input.formatted.flow_type |= IXGBE_ATR_L4TYPE_TUNNEL_MASK;

	/* This assumes the Rx queue and Tx queue are bound to the same CPU */
	ixgbe_fdir_add_signature_filter_82599(&q_vector->adapter->hw,
					      input, common, ring->queue_index);
}