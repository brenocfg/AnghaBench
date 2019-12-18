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
typedef  int u64 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ csum_offset; scalar_t__ encapsulation; } ;
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;
struct TYPE_8__ {int version; int protocol; } ;
struct TYPE_7__ {int nexthdr; } ;
struct TYPE_6__ {int version; int protocol; } ;
struct TYPE_5__ {int nexthdr; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int) ; 
 scalar_t__ CHELSIO_T5 ; 
 int ETH_HLEN ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int T6_TXPKT_ETHHDR_LEN_V (int) ; 
 int TXPKT_CSUM_LOC_V (scalar_t__) ; 
 int TXPKT_CSUM_START_V (int) ; 
 int TXPKT_CSUM_TYPE_V (int) ; 
 int TXPKT_ETHHDR_LEN_V (int) ; 
 int TXPKT_IPHDR_LEN_V (int) ; 
 int TXPKT_L4CSUM_DIS_F ; 
 int TX_CSUM_TCPIP ; 
 int TX_CSUM_TCPIP6 ; 
 int TX_CSUM_UDPIP ; 
 int TX_CSUM_UDPIP6 ; 
 TYPE_4__* inner_ip_hdr (struct sk_buff const*) ; 
 TYPE_3__* inner_ipv6_hdr (struct sk_buff const*) ; 
 TYPE_2__* ip_hdr (struct sk_buff const*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 
 scalar_t__ likely (int) ; 
 int skb_inner_network_header_len (struct sk_buff const*) ; 
 int skb_inner_network_offset (struct sk_buff const*) ; 
 int skb_network_header_len (struct sk_buff const*) ; 
 int skb_network_offset (struct sk_buff const*) ; 
 int skb_transport_offset (struct sk_buff const*) ; 

__attribute__((used)) static u64 hwcsum(enum chip_type chip, const struct sk_buff *skb)
{
	int csum_type;
	bool inner_hdr_csum = false;
	u16 proto, ver;

	if (skb->encapsulation &&
	    (CHELSIO_CHIP_VERSION(chip) > CHELSIO_T5))
		inner_hdr_csum = true;

	if (inner_hdr_csum) {
		ver = inner_ip_hdr(skb)->version;
		proto = (ver == 4) ? inner_ip_hdr(skb)->protocol :
			inner_ipv6_hdr(skb)->nexthdr;
	} else {
		ver = ip_hdr(skb)->version;
		proto = (ver == 4) ? ip_hdr(skb)->protocol :
			ipv6_hdr(skb)->nexthdr;
	}

	if (ver == 4) {
		if (proto == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP;
		else if (proto == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP;
		else {
nocsum:			/*
			 * unknown protocol, disable HW csum
			 * and hope a bad packet is detected
			 */
			return TXPKT_L4CSUM_DIS_F;
		}
	} else {
		/*
		 * this doesn't work with extension headers
		 */
		if (proto == IPPROTO_TCP)
			csum_type = TX_CSUM_TCPIP6;
		else if (proto == IPPROTO_UDP)
			csum_type = TX_CSUM_UDPIP6;
		else
			goto nocsum;
	}

	if (likely(csum_type >= TX_CSUM_TCPIP)) {
		int eth_hdr_len, l4_len;
		u64 hdr_len;

		if (inner_hdr_csum) {
			/* This allows checksum offload for all encapsulated
			 * packets like GRE etc..
			 */
			l4_len = skb_inner_network_header_len(skb);
			eth_hdr_len = skb_inner_network_offset(skb) - ETH_HLEN;
		} else {
			l4_len = skb_network_header_len(skb);
			eth_hdr_len = skb_network_offset(skb) - ETH_HLEN;
		}
		hdr_len = TXPKT_IPHDR_LEN_V(l4_len);

		if (CHELSIO_CHIP_VERSION(chip) <= CHELSIO_T5)
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