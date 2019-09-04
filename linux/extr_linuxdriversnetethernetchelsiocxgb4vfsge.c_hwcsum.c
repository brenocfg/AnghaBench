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
typedef  int u64 ;
struct sk_buff {scalar_t__ csum_offset; } ;
struct ipv6hdr {scalar_t__ nexthdr; } ;
struct iphdr {int version; scalar_t__ protocol; } ;
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;

/* Variables and functions */
 int CHELSIO_T5 ; 
 int ETH_HLEN ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int T6_TXPKT_ETHHDR_LEN_V (int) ; 
 int TXPKT_CSUM_LOC_V (scalar_t__) ; 
 int TXPKT_CSUM_START_V (int) ; 
 int TXPKT_CSUM_TYPE_V (int) ; 
 int TXPKT_ETHHDR_LEN_V (int) ; 
 int TXPKT_IPHDR_LEN_V (int /*<<< orphan*/ ) ; 
 int TXPKT_L4CSUM_DIS_F ; 
 int TX_CSUM_TCPIP ; 
 int TX_CSUM_TCPIP6 ; 
 int TX_CSUM_UDPIP ; 
 int TX_CSUM_UDPIP6 ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff const*) ; 
 int skb_network_offset (struct sk_buff const*) ; 
 int skb_transport_offset (struct sk_buff const*) ; 

__attribute__((used)) static u64 hwcsum(enum chip_type chip, const struct sk_buff *skb)
{
	int csum_type;
	const struct iphdr *iph = ip_hdr(skb);

	if (iph->version == 4) {
		if (iph->protocol == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP;
		else if (iph->protocol == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP;
		else {
nocsum:
			/*
			 * unknown protocol, disable HW csum
			 * and hope a bad packet is detected
			 */
			return TXPKT_L4CSUM_DIS_F;
		}
	} else {
		/*
		 * this doesn't work with extension headers
		 */
		const struct ipv6hdr *ip6h = (const struct ipv6hdr *)iph;

		if (ip6h->nexthdr == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP6;
		else if (ip6h->nexthdr == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP6;
		else
			goto nocsum;
	}

	if (likely(csum_type >= TX_CSUM_TCPIP)) {
		u64 hdr_len = TXPKT_IPHDR_LEN_V(skb_network_header_len(skb));
		int eth_hdr_len = skb_network_offset(skb) - ETH_HLEN;

		if (chip <= CHELSIO_T5)
			hdr_len |= TXPKT_ETHHDR_LEN_V(eth_hdr_len);
		else
			hdr_len |= T6_TXPKT_ETHHDR_LEN_V(eth_hdr_len);
		return TXPKT_CSUM_TYPE_V(csum_type) | hdr_len;
	} else {
		int start = skb_transport_offset(skb);

		return TXPKT_CSUM_TYPE_V(csum_type) |
			TXPKT_CSUM_START_V(start) |
			TXPKT_CSUM_LOC_V(start + skb->csum_offset);
	}
}