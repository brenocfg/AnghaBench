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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vlan_ethhdr {scalar_t__ h_vlan_encapsulated_proto; void* h_vlan_TCI; void* h_vlan_proto; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ ip_summed; scalar_t__ data; } ;
struct nx_host_tx_ring {size_t producer; int /*<<< orphan*/  num_desc; TYPE_1__* cmd_buf_arr; struct cmd_desc_type0* desc_head; } ;
struct net_device {int features; } ;
struct cmd_desc_type0 {int total_hdr_length; int tcp_hdr_offset; int ip_hdr_offset; int /*<<< orphan*/  mss; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_8__ {scalar_t__ protocol; } ;
struct TYPE_7__ {scalar_t__ nexthdr; } ;
struct TYPE_6__ {scalar_t__ gso_size; } ;
struct TYPE_5__ {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLAGS_VLAN_OOB ; 
 int /*<<< orphan*/  FLAGS_VLAN_TAGGED ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 scalar_t__ TX_ETHER_PKT ; 
 scalar_t__ TX_TCPV6_PKT ; 
 scalar_t__ TX_TCP_LSO ; 
 scalar_t__ TX_TCP_LSO6 ; 
 scalar_t__ TX_TCP_PKT ; 
 scalar_t__ TX_UDPV6_PKT ; 
 scalar_t__ TX_UDP_PKT ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 size_t get_next_index (size_t,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  netxen_set_tx_flags_opcode (struct cmd_desc_type0*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netxen_set_tx_vlan_tci (struct cmd_desc_type0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,struct vlan_ethhdr*,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,char*,int) ; 
 int skb_network_offset (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static void
netxen_tso_check(struct net_device *netdev,
		struct nx_host_tx_ring *tx_ring,
		struct cmd_desc_type0 *first_desc,
		struct sk_buff *skb)
{
	u8 opcode = TX_ETHER_PKT;
	__be16 protocol = skb->protocol;
	u16 flags = 0, vid = 0;
	u32 producer;
	int copied, offset, copy_len, hdr_len = 0, tso = 0, vlan_oob = 0;
	struct cmd_desc_type0 *hwdesc;
	struct vlan_ethhdr *vh;

	if (protocol == cpu_to_be16(ETH_P_8021Q)) {

		vh = (struct vlan_ethhdr *)skb->data;
		protocol = vh->h_vlan_encapsulated_proto;
		flags = FLAGS_VLAN_TAGGED;

	} else if (skb_vlan_tag_present(skb)) {
		flags = FLAGS_VLAN_OOB;
		vid = skb_vlan_tag_get(skb);
		netxen_set_tx_vlan_tci(first_desc, vid);
		vlan_oob = 1;
	}

	if ((netdev->features & (NETIF_F_TSO | NETIF_F_TSO6)) &&
			skb_shinfo(skb)->gso_size > 0) {

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);

		first_desc->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
		first_desc->total_hdr_length = hdr_len;
		if (vlan_oob) {
			first_desc->total_hdr_length += VLAN_HLEN;
			first_desc->tcp_hdr_offset = VLAN_HLEN;
			first_desc->ip_hdr_offset = VLAN_HLEN;
			/* Only in case of TSO on vlan device */
			flags |= FLAGS_VLAN_TAGGED;
		}

		opcode = (protocol == cpu_to_be16(ETH_P_IPV6)) ?
				TX_TCP_LSO6 : TX_TCP_LSO;
		tso = 1;

	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		u8 l4proto;

		if (protocol == cpu_to_be16(ETH_P_IP)) {
			l4proto = ip_hdr(skb)->protocol;

			if (l4proto == IPPROTO_TCP)
				opcode = TX_TCP_PKT;
			else if(l4proto == IPPROTO_UDP)
				opcode = TX_UDP_PKT;
		} else if (protocol == cpu_to_be16(ETH_P_IPV6)) {
			l4proto = ipv6_hdr(skb)->nexthdr;

			if (l4proto == IPPROTO_TCP)
				opcode = TX_TCPV6_PKT;
			else if(l4proto == IPPROTO_UDP)
				opcode = TX_UDPV6_PKT;
		}
	}

	first_desc->tcp_hdr_offset += skb_transport_offset(skb);
	first_desc->ip_hdr_offset += skb_network_offset(skb);
	netxen_set_tx_flags_opcode(first_desc, flags, opcode);

	if (!tso)
		return;

	/* For LSO, we need to copy the MAC/IP/TCP headers into
	 * the descriptor ring
	 */
	producer = tx_ring->producer;
	copied = 0;
	offset = 2;

	if (vlan_oob) {
		/* Create a TSO vlan header template for firmware */

		hwdesc = &tx_ring->desc_head[producer];
		tx_ring->cmd_buf_arr[producer].skb = NULL;

		copy_len = min((int)sizeof(struct cmd_desc_type0) - offset,
				hdr_len + VLAN_HLEN);

		vh = (struct vlan_ethhdr *)((char *)hwdesc + 2);
		skb_copy_from_linear_data(skb, vh, 12);
		vh->h_vlan_proto = htons(ETH_P_8021Q);
		vh->h_vlan_TCI = htons(vid);
		skb_copy_from_linear_data_offset(skb, 12,
				(char *)vh + 16, copy_len - 16);

		copied = copy_len - VLAN_HLEN;
		offset = 0;

		producer = get_next_index(producer, tx_ring->num_desc);
	}

	while (copied < hdr_len) {

		copy_len = min((int)sizeof(struct cmd_desc_type0) - offset,
				(hdr_len - copied));

		hwdesc = &tx_ring->desc_head[producer];
		tx_ring->cmd_buf_arr[producer].skb = NULL;

		skb_copy_from_linear_data_offset(skb, copied,
				 (char *)hwdesc + offset, copy_len);

		copied += copy_len;
		offset = 0;

		producer = get_next_index(producer, tx_ring->num_desc);
	}

	tx_ring->producer = producer;
	barrier();
}