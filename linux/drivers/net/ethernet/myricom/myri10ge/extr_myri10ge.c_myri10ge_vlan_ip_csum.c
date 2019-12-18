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
struct vlan_hdr {scalar_t__ h_vlan_encapsulated_proto; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void myri10ge_vlan_ip_csum(struct sk_buff *skb, __wsum hw_csum)
{
	struct vlan_hdr *vh = (struct vlan_hdr *)(skb->data);

	if ((skb->protocol == htons(ETH_P_8021Q)) &&
	    (vh->h_vlan_encapsulated_proto == htons(ETH_P_IP) ||
	     vh->h_vlan_encapsulated_proto == htons(ETH_P_IPV6))) {
		skb->csum = hw_csum;
		skb->ip_summed = CHECKSUM_COMPLETE;
	}
}