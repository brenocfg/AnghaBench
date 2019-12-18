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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {size_t* pcp_to_vl_mc; size_t* pcp_to_vl_uc; size_t non_vlan_vl_mc; size_t non_vlan_vl_uc; } ;
struct __opa_veswport_info {TYPE_1__ vport; } ;
struct opa_vnic_adapter {struct __opa_veswport_info info; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 size_t VLAN_PRIO_SHIFT ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 size_t skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

u8 opa_vnic_get_vl(struct opa_vnic_adapter *adapter, struct sk_buff *skb)
{
	struct ethhdr *mac_hdr = (struct ethhdr *)skb_mac_header(skb);
	struct __opa_veswport_info *info = &adapter->info;
	u8 vl;

	if (skb_vlan_tag_present(skb)) {
		u8 pcp = skb_vlan_tag_get(skb) >> VLAN_PRIO_SHIFT;

		if (is_multicast_ether_addr(mac_hdr->h_dest))
			vl = info->vport.pcp_to_vl_mc[pcp];
		else
			vl = info->vport.pcp_to_vl_uc[pcp];
	} else {
		if (is_multicast_ether_addr(mac_hdr->h_dest))
			vl = info->vport.non_vlan_vl_mc;
		else
			vl = info->vport.non_vlan_vl_uc;
	}

	return vl;
}