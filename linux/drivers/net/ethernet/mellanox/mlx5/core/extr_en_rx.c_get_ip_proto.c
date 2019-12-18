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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {void* data; } ;
struct ipv6hdr {int /*<<< orphan*/  nexthdr; } ;
struct iphdr {int /*<<< orphan*/  protocol; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 get_ip_proto(struct sk_buff *skb, int network_depth, __be16 proto)
{
	void *ip_p = skb->data + network_depth;

	return (proto == htons(ETH_P_IP)) ? ((struct iphdr *)ip_p)->protocol :
					    ((struct ipv6hdr *)ip_p)->nexthdr;
}