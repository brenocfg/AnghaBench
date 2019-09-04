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
struct sk_buff {int dummy; } ;
struct in6_addr {int dummy; } ;
struct arfs_tuple {scalar_t__ etype; scalar_t__ src_ipv4; scalar_t__ dst_ipv4; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; } ;
struct TYPE_4__ {scalar_t__ saddr; scalar_t__ daddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff const*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool arfs_cmp_ips(struct arfs_tuple *tuple,
			 const struct sk_buff *skb)
{
	if (tuple->etype == htons(ETH_P_IP) &&
	    tuple->src_ipv4 == ip_hdr(skb)->saddr &&
	    tuple->dst_ipv4 == ip_hdr(skb)->daddr)
		return true;
	if (tuple->etype == htons(ETH_P_IPV6) &&
	    (!memcmp(&tuple->src_ipv6, &ipv6_hdr(skb)->saddr,
		     sizeof(struct in6_addr))) &&
	    (!memcmp(&tuple->dst_ipv6, &ipv6_hdr(skb)->daddr,
		     sizeof(struct in6_addr))))
		return true;
	return false;
}