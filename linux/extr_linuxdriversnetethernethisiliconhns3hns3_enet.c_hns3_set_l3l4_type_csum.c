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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {scalar_t__ protocol; scalar_t__ encapsulation; } ;
struct ipv6hdr {int version; } ;
struct iphdr {int version; } ;

/* Variables and functions */
 int EDOM ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  HNS3_L3T_IPV4 ; 
 int /*<<< orphan*/  HNS3_L3T_IPV6 ; 
 int /*<<< orphan*/  HNS3_L4T_SCTP ; 
 int /*<<< orphan*/  HNS3_L4T_TCP ; 
 int /*<<< orphan*/  HNS3_L4T_UDP ; 
 int /*<<< orphan*/  HNS3_OL3T_IPV4_CSUM ; 
 int /*<<< orphan*/  HNS3_OL3T_IPV4_NO_CSUM ; 
 int /*<<< orphan*/  HNS3_OL3T_IPV6 ; 
 int /*<<< orphan*/  HNS3_TUN_MAC_IN_UDP ; 
 int /*<<< orphan*/  HNS3_TUN_NVGRE ; 
 int /*<<< orphan*/  HNS3_TXD_L3CS_B ; 
 int /*<<< orphan*/  HNS3_TXD_L3T_M ; 
 int /*<<< orphan*/  HNS3_TXD_L3T_S ; 
 int /*<<< orphan*/  HNS3_TXD_L4CS_B ; 
 int /*<<< orphan*/  HNS3_TXD_L4T_M ; 
 int /*<<< orphan*/  HNS3_TXD_L4T_S ; 
 int /*<<< orphan*/  HNS3_TXD_OL3T_M ; 
 int /*<<< orphan*/  HNS3_TXD_OL3T_S ; 
 int /*<<< orphan*/  HNS3_TXD_TUNTYPE_M ; 
 int /*<<< orphan*/  HNS3_TXD_TUNTYPE_S ; 
#define  IPPROTO_GRE 131 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  hnae3_set_bit (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_tunnel_csum_bug (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_help (struct sk_buff*) ; 
 unsigned char* skb_inner_network_header (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int hns3_set_l3l4_type_csum(struct sk_buff *skb, u8 ol4_proto,
				   u8 il4_proto, u32 *type_cs_vlan_tso,
				   u32 *ol_type_vlan_len_msec)
{
	union {
		struct iphdr *v4;
		struct ipv6hdr *v6;
		unsigned char *hdr;
	} l3;
	u32 l4_proto = ol4_proto;

	l3.hdr = skb_network_header(skb);

	/* define OL3 type and tunnel type(OL4).*/
	if (skb->encapsulation) {
		/* define outer network header type.*/
		if (skb->protocol == htons(ETH_P_IP)) {
			if (skb_is_gso(skb))
				hnae3_set_field(*ol_type_vlan_len_msec,
						HNS3_TXD_OL3T_M,
						HNS3_TXD_OL3T_S,
						HNS3_OL3T_IPV4_CSUM);
			else
				hnae3_set_field(*ol_type_vlan_len_msec,
						HNS3_TXD_OL3T_M,
						HNS3_TXD_OL3T_S,
						HNS3_OL3T_IPV4_NO_CSUM);

		} else if (skb->protocol == htons(ETH_P_IPV6)) {
			hnae3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_OL3T_M,
					HNS3_TXD_OL3T_S, HNS3_OL3T_IPV6);
		}

		/* define tunnel type(OL4).*/
		switch (l4_proto) {
		case IPPROTO_UDP:
			hnae3_set_field(*ol_type_vlan_len_msec,
					HNS3_TXD_TUNTYPE_M,
					HNS3_TXD_TUNTYPE_S,
					HNS3_TUN_MAC_IN_UDP);
			break;
		case IPPROTO_GRE:
			hnae3_set_field(*ol_type_vlan_len_msec,
					HNS3_TXD_TUNTYPE_M,
					HNS3_TXD_TUNTYPE_S,
					HNS3_TUN_NVGRE);
			break;
		default:
			/* drop the skb tunnel packet if hardware don't support,
			 * because hardware can't calculate csum when TSO.
			 */
			if (skb_is_gso(skb))
				return -EDOM;

			/* the stack computes the IP header already,
			 * driver calculate l4 checksum when not TSO.
			 */
			skb_checksum_help(skb);
			return 0;
		}

		l3.hdr = skb_inner_network_header(skb);
		l4_proto = il4_proto;
	}

	if (l3.v4->version == 4) {
		hnae3_set_field(*type_cs_vlan_tso, HNS3_TXD_L3T_M,
				HNS3_TXD_L3T_S, HNS3_L3T_IPV4);

		/* the stack computes the IP header already, the only time we
		 * need the hardware to recompute it is in the case of TSO.
		 */
		if (skb_is_gso(skb))
			hnae3_set_bit(*type_cs_vlan_tso, HNS3_TXD_L3CS_B, 1);
	} else if (l3.v6->version == 6) {
		hnae3_set_field(*type_cs_vlan_tso, HNS3_TXD_L3T_M,
				HNS3_TXD_L3T_S, HNS3_L3T_IPV6);
	}

	switch (l4_proto) {
	case IPPROTO_TCP:
		hnae3_set_bit(*type_cs_vlan_tso, HNS3_TXD_L4CS_B, 1);
		hnae3_set_field(*type_cs_vlan_tso,
				HNS3_TXD_L4T_M,
				HNS3_TXD_L4T_S,
				HNS3_L4T_TCP);
		break;
	case IPPROTO_UDP:
		if (hns3_tunnel_csum_bug(skb))
			break;

		hnae3_set_bit(*type_cs_vlan_tso, HNS3_TXD_L4CS_B, 1);
		hnae3_set_field(*type_cs_vlan_tso,
				HNS3_TXD_L4T_M,
				HNS3_TXD_L4T_S,
				HNS3_L4T_UDP);
		break;
	case IPPROTO_SCTP:
		hnae3_set_bit(*type_cs_vlan_tso, HNS3_TXD_L4CS_B, 1);
		hnae3_set_field(*type_cs_vlan_tso,
				HNS3_TXD_L4T_M,
				HNS3_TXD_L4T_S,
				HNS3_L4T_SCTP);
		break;
	default:
		/* drop the skb tunnel packet if hardware don't support,
		 * because hardware can't calculate csum when TSO.
		 */
		if (skb_is_gso(skb))
			return -EDOM;

		/* the stack computes the IP header already,
		 * driver calculate l4 checksum when not TSO.
		 */
		skb_checksum_help(skb);
		return 0;
	}

	return 0;
}