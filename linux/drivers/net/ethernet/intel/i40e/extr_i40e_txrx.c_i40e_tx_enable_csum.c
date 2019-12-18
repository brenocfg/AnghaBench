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
typedef  int u8 ;
typedef  int u32 ;
struct udphdr {int dummy; } ;
struct tcphdr {int doff; } ;
struct sk_buff {scalar_t__ ip_summed; unsigned char* data; scalar_t__ encapsulation; } ;
struct sctphdr {int dummy; } ;
struct ipv6hdr {int nexthdr; int version; } ;
struct iphdr {int protocol; int version; } ;
struct i40e_ring {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int I40E_TXD_CTX_GRE_TUNNELING ; 
 int I40E_TXD_CTX_QW0_EXT_IPLEN_SHIFT ; 
 int I40E_TXD_CTX_QW0_L4T_CS_MASK ; 
 int I40E_TXD_CTX_QW0_NATLEN_SHIFT ; 
 int I40E_TXD_CTX_UDP_TUNNELING ; 
 int I40E_TX_CTX_EXT_IP_IPV4 ; 
 int I40E_TX_CTX_EXT_IP_IPV4_NO_CSUM ; 
 int I40E_TX_CTX_EXT_IP_IPV6 ; 
 int I40E_TX_DESC_CMD_IIPT_IPV4 ; 
 int I40E_TX_DESC_CMD_IIPT_IPV4_CSUM ; 
 int I40E_TX_DESC_CMD_IIPT_IPV6 ; 
 int I40E_TX_DESC_CMD_L4T_EOFT_SCTP ; 
 int I40E_TX_DESC_CMD_L4T_EOFT_TCP ; 
 int I40E_TX_DESC_CMD_L4T_EOFT_UDP ; 
 int I40E_TX_DESC_LENGTH_IPLEN_SHIFT ; 
 int I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT ; 
 int I40E_TX_DESC_LENGTH_MACLEN_SHIFT ; 
 int I40E_TX_FLAGS_IPV4 ; 
 int I40E_TX_FLAGS_IPV6 ; 
 int I40E_TX_FLAGS_TSO ; 
 int I40E_TX_FLAGS_UDP_TUNNEL ; 
#define  IPPROTO_GRE 133 
#define  IPPROTO_IPIP 132 
#define  IPPROTO_IPV6 131 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int SKB_GSO_PARTIAL ; 
 int SKB_GSO_UDP_TUNNEL_CSUM ; 
 int /*<<< orphan*/  ipv6_skip_exthdr (struct sk_buff*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_checksum_help (struct sk_buff*) ; 
 void* skb_inner_network_header (struct sk_buff*) ; 
 unsigned char* skb_inner_transport_header (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 unsigned char* skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int i40e_tx_enable_csum(struct sk_buff *skb, u32 *tx_flags,
			       u32 *td_cmd, u32 *td_offset,
			       struct i40e_ring *tx_ring,
			       u32 *cd_tunneling)
{
	union {
		struct iphdr *v4;
		struct ipv6hdr *v6;
		unsigned char *hdr;
	} ip;
	union {
		struct tcphdr *tcp;
		struct udphdr *udp;
		unsigned char *hdr;
	} l4;
	unsigned char *exthdr;
	u32 offset, cmd = 0;
	__be16 frag_off;
	u8 l4_proto = 0;

	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return 0;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* compute outer L2 header size */
	offset = ((ip.hdr - skb->data) / 2) << I40E_TX_DESC_LENGTH_MACLEN_SHIFT;

	if (skb->encapsulation) {
		u32 tunnel = 0;
		/* define outer network header type */
		if (*tx_flags & I40E_TX_FLAGS_IPV4) {
			tunnel |= (*tx_flags & I40E_TX_FLAGS_TSO) ?
				  I40E_TX_CTX_EXT_IP_IPV4 :
				  I40E_TX_CTX_EXT_IP_IPV4_NO_CSUM;

			l4_proto = ip.v4->protocol;
		} else if (*tx_flags & I40E_TX_FLAGS_IPV6) {
			tunnel |= I40E_TX_CTX_EXT_IP_IPV6;

			exthdr = ip.hdr + sizeof(*ip.v6);
			l4_proto = ip.v6->nexthdr;
			if (l4.hdr != exthdr)
				ipv6_skip_exthdr(skb, exthdr - skb->data,
						 &l4_proto, &frag_off);
		}

		/* define outer transport */
		switch (l4_proto) {
		case IPPROTO_UDP:
			tunnel |= I40E_TXD_CTX_UDP_TUNNELING;
			*tx_flags |= I40E_TX_FLAGS_UDP_TUNNEL;
			break;
		case IPPROTO_GRE:
			tunnel |= I40E_TXD_CTX_GRE_TUNNELING;
			*tx_flags |= I40E_TX_FLAGS_UDP_TUNNEL;
			break;
		case IPPROTO_IPIP:
		case IPPROTO_IPV6:
			*tx_flags |= I40E_TX_FLAGS_UDP_TUNNEL;
			l4.hdr = skb_inner_network_header(skb);
			break;
		default:
			if (*tx_flags & I40E_TX_FLAGS_TSO)
				return -1;

			skb_checksum_help(skb);
			return 0;
		}

		/* compute outer L3 header size */
		tunnel |= ((l4.hdr - ip.hdr) / 4) <<
			  I40E_TXD_CTX_QW0_EXT_IPLEN_SHIFT;

		/* switch IP header pointer from outer to inner header */
		ip.hdr = skb_inner_network_header(skb);

		/* compute tunnel header size */
		tunnel |= ((ip.hdr - l4.hdr) / 2) <<
			  I40E_TXD_CTX_QW0_NATLEN_SHIFT;

		/* indicate if we need to offload outer UDP header */
		if ((*tx_flags & I40E_TX_FLAGS_TSO) &&
		    !(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM))
			tunnel |= I40E_TXD_CTX_QW0_L4T_CS_MASK;

		/* record tunnel offload values */
		*cd_tunneling |= tunnel;

		/* switch L4 header pointer from outer to inner */
		l4.hdr = skb_inner_transport_header(skb);
		l4_proto = 0;

		/* reset type as we transition from outer to inner headers */
		*tx_flags &= ~(I40E_TX_FLAGS_IPV4 | I40E_TX_FLAGS_IPV6);
		if (ip.v4->version == 4)
			*tx_flags |= I40E_TX_FLAGS_IPV4;
		if (ip.v6->version == 6)
			*tx_flags |= I40E_TX_FLAGS_IPV6;
	}

	/* Enable IP checksum offloads */
	if (*tx_flags & I40E_TX_FLAGS_IPV4) {
		l4_proto = ip.v4->protocol;
		/* the stack computes the IP header already, the only time we
		 * need the hardware to recompute it is in the case of TSO.
		 */
		cmd |= (*tx_flags & I40E_TX_FLAGS_TSO) ?
		       I40E_TX_DESC_CMD_IIPT_IPV4_CSUM :
		       I40E_TX_DESC_CMD_IIPT_IPV4;
	} else if (*tx_flags & I40E_TX_FLAGS_IPV6) {
		cmd |= I40E_TX_DESC_CMD_IIPT_IPV6;

		exthdr = ip.hdr + sizeof(*ip.v6);
		l4_proto = ip.v6->nexthdr;
		if (l4.hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto, &frag_off);
	}

	/* compute inner L3 header size */
	offset |= ((l4.hdr - ip.hdr) / 4) << I40E_TX_DESC_LENGTH_IPLEN_SHIFT;

	/* Enable L4 checksum offloads */
	switch (l4_proto) {
	case IPPROTO_TCP:
		/* enable checksum offloads */
		cmd |= I40E_TX_DESC_CMD_L4T_EOFT_TCP;
		offset |= l4.tcp->doff << I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		break;
	case IPPROTO_SCTP:
		/* enable SCTP checksum offload */
		cmd |= I40E_TX_DESC_CMD_L4T_EOFT_SCTP;
		offset |= (sizeof(struct sctphdr) >> 2) <<
			  I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		break;
	case IPPROTO_UDP:
		/* enable UDP checksum offload */
		cmd |= I40E_TX_DESC_CMD_L4T_EOFT_UDP;
		offset |= (sizeof(struct udphdr) >> 2) <<
			  I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		break;
	default:
		if (*tx_flags & I40E_TX_FLAGS_TSO)
			return -1;
		skb_checksum_help(skb);
		return 0;
	}

	*td_cmd |= cmd;
	*td_offset |= offset;

	return 1;
}