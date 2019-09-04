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
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {scalar_t__ h_proto; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ __vlan_get_protocol (struct sk_buff*,scalar_t__,int*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_last_ethertype_ip(struct sk_buff *skb, int *network_depth)
{
	__be16 ethertype = ((struct ethhdr *)skb->data)->h_proto;

	ethertype = __vlan_get_protocol(skb, ethertype, network_depth);
	return (ethertype == htons(ETH_P_IP) || ethertype == htons(ETH_P_IPV6));
}