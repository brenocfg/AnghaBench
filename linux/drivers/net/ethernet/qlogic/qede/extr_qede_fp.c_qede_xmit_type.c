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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_4__ {scalar_t__ nexthdr; } ;
struct TYPE_3__ {unsigned short gso_type; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ NEXTHDR_IPV6 ; 
 unsigned short SKB_GSO_GRE_CSUM ; 
 unsigned short SKB_GSO_UDP_TUNNEL_CSUM ; 
 int /*<<< orphan*/  XMIT_ENC ; 
 int /*<<< orphan*/  XMIT_ENC_GSO_L4_CSUM ; 
 int /*<<< orphan*/  XMIT_L4_CSUM ; 
 int /*<<< orphan*/  XMIT_LSO ; 
 int /*<<< orphan*/  XMIT_PLAIN ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static u32 qede_xmit_type(struct sk_buff *skb, int *ipv6_ext)
{
	u32 rc = XMIT_L4_CSUM;
	__be16 l3_proto;

	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return XMIT_PLAIN;

	l3_proto = vlan_get_protocol(skb);
	if (l3_proto == htons(ETH_P_IPV6) &&
	    (ipv6_hdr(skb)->nexthdr == NEXTHDR_IPV6))
		*ipv6_ext = 1;

	if (skb->encapsulation) {
		rc |= XMIT_ENC;
		if (skb_is_gso(skb)) {
			unsigned short gso_type = skb_shinfo(skb)->gso_type;

			if ((gso_type & SKB_GSO_UDP_TUNNEL_CSUM) ||
			    (gso_type & SKB_GSO_GRE_CSUM))
				rc |= XMIT_ENC_GSO_L4_CSUM;

			rc |= XMIT_LSO;
			return rc;
		}
	}

	if (skb_is_gso(skb))
		rc |= XMIT_LSO;

	return rc;
}