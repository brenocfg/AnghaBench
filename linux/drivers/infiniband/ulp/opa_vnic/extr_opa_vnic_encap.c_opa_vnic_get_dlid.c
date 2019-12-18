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
typedef  int uint32_t ;
typedef  size_t u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int u_mcast_dlid; int* u_ucast_dlid; } ;
struct __opa_veswport_info {TYPE_1__ vesw; } ;
struct opa_vnic_adapter {struct __opa_veswport_info info; } ;
struct ethhdr {int* h_dest; } ;

/* Variables and functions */
 size_t OPA_VESW_MAX_NUM_DEF_PORT ; 
 size_t OPA_VNIC_INVALID_PORT ; 
 scalar_t__ is_local_ether_addr (int*) ; 
 scalar_t__ is_multicast_ether_addr (int*) ; 
 int opa_vnic_chk_mac_tbl (struct opa_vnic_adapter*,struct ethhdr*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v_warn (char*) ; 

__attribute__((used)) static uint32_t opa_vnic_get_dlid(struct opa_vnic_adapter *adapter,
				  struct sk_buff *skb, u8 def_port)
{
	struct __opa_veswport_info *info = &adapter->info;
	struct ethhdr *mac_hdr = (struct ethhdr *)skb_mac_header(skb);
	u32 dlid;

	dlid = opa_vnic_chk_mac_tbl(adapter, mac_hdr);
	if (dlid)
		return dlid;

	if (is_multicast_ether_addr(mac_hdr->h_dest)) {
		dlid = info->vesw.u_mcast_dlid;
	} else {
		if (is_local_ether_addr(mac_hdr->h_dest)) {
			dlid = ((uint32_t)mac_hdr->h_dest[5] << 16) |
				((uint32_t)mac_hdr->h_dest[4] << 8)  |
				mac_hdr->h_dest[3];
			if (unlikely(!dlid))
				v_warn("Null dlid in MAC address\n");
		} else if (def_port != OPA_VNIC_INVALID_PORT) {
			if (def_port < OPA_VESW_MAX_NUM_DEF_PORT)
				dlid = info->vesw.u_ucast_dlid[def_port];
		}
	}

	return dlid;
}