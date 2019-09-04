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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {scalar_t__ nexthdr; } ;

/* Variables and functions */
 int ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR ; 
 scalar_t__ NEXTHDR_IPV6 ; 
 int XMIT_GSO_ENC_V6 ; 
 int XMIT_GSO_V6 ; 
 struct ipv6hdr* inner_ipv6_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void bnx2x_set_ipv6_ext_e2(struct sk_buff *skb, u32 *parsing_data,
					 u32 xmit_type)
{
	struct ipv6hdr *ipv6;

	if (!(xmit_type & (XMIT_GSO_ENC_V6 | XMIT_GSO_V6)))
		return;

	if (xmit_type & XMIT_GSO_ENC_V6)
		ipv6 = inner_ipv6_hdr(skb);
	else /* XMIT_GSO_V6 */
		ipv6 = ipv6_hdr(skb);

	if (ipv6->nexthdr == NEXTHDR_IPV6)
		*parsing_data |= ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR;
}