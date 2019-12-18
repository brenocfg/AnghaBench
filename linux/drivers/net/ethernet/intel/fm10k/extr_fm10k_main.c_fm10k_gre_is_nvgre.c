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
struct sk_buff {int dummy; } ;
struct fm10k_nvgre_hdr {int flags; int /*<<< orphan*/  tni; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int FM10K_NVGRE_RESERVED0_FLAGS ; 
 int NVGRE_TNI ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static struct ethhdr *fm10k_gre_is_nvgre(struct sk_buff *skb)
{
	struct fm10k_nvgre_hdr *nvgre_hdr;
	int hlen = ip_hdrlen(skb);

	/* currently only IPv4 is supported due to hlen above */
	if (vlan_get_protocol(skb) != htons(ETH_P_IP))
		return NULL;

	/* our transport header should be NVGRE */
	nvgre_hdr = (struct fm10k_nvgre_hdr *)(skb_network_header(skb) + hlen);

	/* verify all reserved flags are 0 */
	if (nvgre_hdr->flags & FM10K_NVGRE_RESERVED0_FLAGS)
		return NULL;

	/* report start of ethernet header */
	if (nvgre_hdr->flags & NVGRE_TNI)
		return (struct ethhdr *)(nvgre_hdr + 1);

	return (struct ethhdr *)(&nvgre_hdr->tni);
}