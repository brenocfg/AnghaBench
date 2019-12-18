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
typedef  int u32 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct bnx2x {int dummy; } ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __be16 ;
struct TYPE_8__ {int version; scalar_t__ protocol; } ;
struct TYPE_7__ {scalar_t__ nexthdr; } ;
struct TYPE_6__ {scalar_t__ protocol; } ;
struct TYPE_5__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 int XMIT_CSUM_ENC ; 
 int XMIT_CSUM_ENC_V4 ; 
 int XMIT_CSUM_ENC_V6 ; 
 int XMIT_CSUM_TCP ; 
 int XMIT_CSUM_V4 ; 
 int XMIT_CSUM_V6 ; 
 int XMIT_GSO_ENC_V4 ; 
 int XMIT_GSO_ENC_V6 ; 
 int XMIT_GSO_V4 ; 
 int XMIT_GSO_V6 ; 
 int XMIT_PLAIN ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* inner_ip_hdr (struct sk_buff*) ; 
 TYPE_3__* inner_ipv6_hdr (struct sk_buff*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_gso_v6 (struct sk_buff*) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static u32 bnx2x_xmit_type(struct bnx2x *bp, struct sk_buff *skb)
{
	u32 rc;
	__u8 prot = 0;
	__be16 protocol;

	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return XMIT_PLAIN;

	protocol = vlan_get_protocol(skb);
	if (protocol == htons(ETH_P_IPV6)) {
		rc = XMIT_CSUM_V6;
		prot = ipv6_hdr(skb)->nexthdr;
	} else {
		rc = XMIT_CSUM_V4;
		prot = ip_hdr(skb)->protocol;
	}

	if (!CHIP_IS_E1x(bp) && skb->encapsulation) {
		if (inner_ip_hdr(skb)->version == 6) {
			rc |= XMIT_CSUM_ENC_V6;
			if (inner_ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
				rc |= XMIT_CSUM_TCP;
		} else {
			rc |= XMIT_CSUM_ENC_V4;
			if (inner_ip_hdr(skb)->protocol == IPPROTO_TCP)
				rc |= XMIT_CSUM_TCP;
		}
	}
	if (prot == IPPROTO_TCP)
		rc |= XMIT_CSUM_TCP;

	if (skb_is_gso(skb)) {
		if (skb_is_gso_v6(skb)) {
			rc |= (XMIT_GSO_V6 | XMIT_CSUM_TCP);
			if (rc & XMIT_CSUM_ENC)
				rc |= XMIT_GSO_ENC_V6;
		} else {
			rc |= (XMIT_GSO_V4 | XMIT_CSUM_TCP);
			if (rc & XMIT_CSUM_ENC)
				rc |= XMIT_GSO_ENC_V4;
		}
	}

	return rc;
}