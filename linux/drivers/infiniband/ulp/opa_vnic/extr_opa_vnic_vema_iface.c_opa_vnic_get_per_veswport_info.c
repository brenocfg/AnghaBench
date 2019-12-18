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
struct __opa_per_veswport_info {int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  mc_macs_gen_count; int /*<<< orphan*/  uc_macs_gen_count; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  non_vlan_vl_mc; int /*<<< orphan*/  non_vlan_sc_mc; int /*<<< orphan*/  non_vlan_vl_uc; int /*<<< orphan*/  non_vlan_sc_uc; int /*<<< orphan*/  pcp_to_vl_mc; int /*<<< orphan*/  pcp_to_sc_mc; int /*<<< orphan*/  pcp_to_vl_uc; int /*<<< orphan*/  pcp_to_sc_uc; int /*<<< orphan*/  encap_slid; int /*<<< orphan*/  rsvd1; int /*<<< orphan*/  mac_tbl_digest; int /*<<< orphan*/  max_smac_ent; int /*<<< orphan*/  max_mac_tbl_ent; int /*<<< orphan*/  oper_state; int /*<<< orphan*/  config_state; int /*<<< orphan*/  base_mac_addr; int /*<<< orphan*/  rsvd0; int /*<<< orphan*/  eth_link_status; int /*<<< orphan*/  port_num; } ;
struct TYPE_2__ {struct __opa_per_veswport_info vport; } ;
struct opa_vnic_adapter {TYPE_1__ info; } ;
struct opa_per_veswport_info {int /*<<< orphan*/  rsvd3; void* mc_macs_gen_count; void* uc_macs_gen_count; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  non_vlan_vl_mc; int /*<<< orphan*/  non_vlan_sc_mc; int /*<<< orphan*/  non_vlan_vl_uc; int /*<<< orphan*/  non_vlan_sc_uc; int /*<<< orphan*/  pcp_to_vl_mc; int /*<<< orphan*/  pcp_to_sc_mc; int /*<<< orphan*/  pcp_to_vl_uc; int /*<<< orphan*/  pcp_to_sc_uc; void* encap_slid; int /*<<< orphan*/  rsvd1; void* mac_tbl_digest; void* max_smac_ent; void* max_mac_tbl_ent; int /*<<< orphan*/  oper_state; int /*<<< orphan*/  config_state; int /*<<< orphan*/  base_mac_addr; int /*<<< orphan*/  rsvd0; int /*<<< orphan*/  eth_link_status; void* port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void opa_vnic_get_per_veswport_info(struct opa_vnic_adapter *adapter,
				    struct opa_per_veswport_info *info)
{
	struct __opa_per_veswport_info *src = &adapter->info.vport;

	info->port_num = cpu_to_be32(src->port_num);
	info->eth_link_status = src->eth_link_status;
	memcpy(info->rsvd0, src->rsvd0, ARRAY_SIZE(src->rsvd0));

	memcpy(info->base_mac_addr, src->base_mac_addr,
	       ARRAY_SIZE(info->base_mac_addr));
	info->config_state = src->config_state;
	info->oper_state = src->oper_state;
	info->max_mac_tbl_ent = cpu_to_be16(src->max_mac_tbl_ent);
	info->max_smac_ent = cpu_to_be16(src->max_smac_ent);
	info->mac_tbl_digest = cpu_to_be32(src->mac_tbl_digest);
	memcpy(info->rsvd1, src->rsvd1, ARRAY_SIZE(src->rsvd1));

	info->encap_slid = cpu_to_be32(src->encap_slid);
	memcpy(info->pcp_to_sc_uc, src->pcp_to_sc_uc,
	       ARRAY_SIZE(info->pcp_to_sc_uc));
	memcpy(info->pcp_to_vl_uc, src->pcp_to_vl_uc,
	       ARRAY_SIZE(info->pcp_to_vl_uc));
	memcpy(info->pcp_to_sc_mc, src->pcp_to_sc_mc,
	       ARRAY_SIZE(info->pcp_to_sc_mc));
	memcpy(info->pcp_to_vl_mc, src->pcp_to_vl_mc,
	       ARRAY_SIZE(info->pcp_to_vl_mc));
	info->non_vlan_sc_uc = src->non_vlan_sc_uc;
	info->non_vlan_vl_uc = src->non_vlan_vl_uc;
	info->non_vlan_sc_mc = src->non_vlan_sc_mc;
	info->non_vlan_vl_mc = src->non_vlan_vl_mc;
	memcpy(info->rsvd2, src->rsvd2, ARRAY_SIZE(src->rsvd2));

	info->uc_macs_gen_count = cpu_to_be16(src->uc_macs_gen_count);
	info->mc_macs_gen_count = cpu_to_be16(src->mc_macs_gen_count);
	memcpy(info->rsvd3, src->rsvd3, ARRAY_SIZE(src->rsvd3));
}