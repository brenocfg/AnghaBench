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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ protocol; } ;
struct ipv6hdr {scalar_t__ nexthdr; } ;
struct iphdr {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV4_TCP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV4_UDP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV6_TCP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV6_UDP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_NOT_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static u32 net_checksum_info(struct sk_buff *skb)
{
	if (skb->protocol == htons(ETH_P_IP)) {
		struct iphdr *ip = ip_hdr(skb);

		if (ip->protocol == IPPROTO_TCP)
			return TRANSPORT_INFO_IPV4_TCP;
		else if (ip->protocol == IPPROTO_UDP)
			return TRANSPORT_INFO_IPV4_UDP;
	} else {
		struct ipv6hdr *ip6 = ipv6_hdr(skb);

		if (ip6->nexthdr == IPPROTO_TCP)
			return TRANSPORT_INFO_IPV6_TCP;
		else if (ip6->nexthdr == IPPROTO_UDP)
			return TRANSPORT_INFO_IPV6_UDP;
	}

	return TRANSPORT_INFO_NOT_IP;
}