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
struct sk_buff {unsigned short protocol; int /*<<< orphan*/  ip_summed; } ;
struct iphdr {unsigned short tot_len; scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  VLAN_HLEN ; 
 unsigned short htons (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void csum_verified(struct sk_buff *skb)
{
	unsigned short protocol;
	struct iphdr *iph;

	protocol = skb->protocol;
	skb_reset_network_header(skb);
	iph = (struct iphdr *) skb_network_header(skb);
	if (protocol == htons(ETH_P_8021Q)) {
		protocol = iph->tot_len;
		skb_set_network_header(skb, VLAN_HLEN);
		iph = (struct iphdr *) skb_network_header(skb);
	}
	if (protocol == htons(ETH_P_IP)) {
		if (iph->protocol == IPPROTO_TCP)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
}