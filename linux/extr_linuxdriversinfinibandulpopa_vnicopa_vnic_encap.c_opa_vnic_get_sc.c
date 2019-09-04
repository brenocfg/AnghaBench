#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct TYPE_2__ {size_t* pcp_to_sc_mc; size_t* pcp_to_sc_uc; size_t non_vlan_sc_mc; size_t non_vlan_sc_uc; } ;
struct __opa_veswport_info {TYPE_1__ vport; } ;

/* Variables and functions */
 size_t OPA_VNIC_VLAN_PCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_get_tag (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static u8 opa_vnic_get_sc(struct __opa_veswport_info *info,
			  struct sk_buff *skb)
{
	struct ethhdr *mac_hdr = (struct ethhdr *)skb_mac_header(skb);
	u16 vlan_tci;
	u8 sc;

	if (!__vlan_get_tag(skb, &vlan_tci)) {
		u8 pcp = OPA_VNIC_VLAN_PCP(vlan_tci);

		if (is_multicast_ether_addr(mac_hdr->h_dest))
			sc = info->vport.pcp_to_sc_mc[pcp];
		else
			sc = info->vport.pcp_to_sc_uc[pcp];
	} else {
		if (is_multicast_ether_addr(mac_hdr->h_dest))
			sc = info->vport.non_vlan_sc_mc;
		else
			sc = info->vport.non_vlan_sc_uc;
	}

	return sc;
}