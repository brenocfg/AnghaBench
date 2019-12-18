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
struct __opa_per_veswport_info {int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  non_vlan_vl_mc; int /*<<< orphan*/  non_vlan_sc_mc; int /*<<< orphan*/  non_vlan_vl_uc; int /*<<< orphan*/  non_vlan_sc_uc; int /*<<< orphan*/  pcp_to_vl_mc; int /*<<< orphan*/  pcp_to_sc_mc; int /*<<< orphan*/  pcp_to_vl_uc; int /*<<< orphan*/  pcp_to_sc_uc; void* encap_slid; int /*<<< orphan*/  rsvd1; int /*<<< orphan*/  config_state; int /*<<< orphan*/  base_mac_addr; int /*<<< orphan*/  rsvd0; void* port_num; } ;
struct TYPE_2__ {struct __opa_per_veswport_info vport; } ;
struct opa_vnic_adapter {TYPE_1__ info; } ;
struct opa_per_veswport_info {int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  non_vlan_vl_mc; int /*<<< orphan*/  non_vlan_sc_mc; int /*<<< orphan*/  non_vlan_vl_uc; int /*<<< orphan*/  non_vlan_sc_uc; int /*<<< orphan*/  pcp_to_vl_mc; int /*<<< orphan*/  pcp_to_sc_mc; int /*<<< orphan*/  pcp_to_vl_uc; int /*<<< orphan*/  pcp_to_sc_uc; int /*<<< orphan*/  encap_slid; int /*<<< orphan*/  rsvd1; int /*<<< orphan*/  config_state; int /*<<< orphan*/  base_mac_addr; int /*<<< orphan*/  rsvd0; int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void opa_vnic_set_per_veswport_info(struct opa_vnic_adapter *adapter,
				    struct opa_per_veswport_info *info)
{
	struct __opa_per_veswport_info *dst = &adapter->info.vport;

	dst->port_num = be32_to_cpu(info->port_num);
	memcpy(dst->rsvd0, info->rsvd0, ARRAY_SIZE(info->rsvd0));

	memcpy(dst->base_mac_addr, info->base_mac_addr,
	       ARRAY_SIZE(dst->base_mac_addr));
	dst->config_state = info->config_state;
	memcpy(dst->rsvd1, info->rsvd1, ARRAY_SIZE(info->rsvd1));

	dst->encap_slid = be32_to_cpu(info->encap_slid);
	memcpy(dst->pcp_to_sc_uc, info->pcp_to_sc_uc,
	       ARRAY_SIZE(dst->pcp_to_sc_uc));
	memcpy(dst->pcp_to_vl_uc, info->pcp_to_vl_uc,
	       ARRAY_SIZE(dst->pcp_to_vl_uc));
	memcpy(dst->pcp_to_sc_mc, info->pcp_to_sc_mc,
	       ARRAY_SIZE(dst->pcp_to_sc_mc));
	memcpy(dst->pcp_to_vl_mc, info->pcp_to_vl_mc,
	       ARRAY_SIZE(dst->pcp_to_vl_mc));
	dst->non_vlan_sc_uc = info->non_vlan_sc_uc;
	dst->non_vlan_vl_uc = info->non_vlan_vl_uc;
	dst->non_vlan_sc_mc = info->non_vlan_sc_mc;
	dst->non_vlan_vl_mc = info->non_vlan_vl_mc;
	memcpy(dst->rsvd2, info->rsvd2, ARRAY_SIZE(info->rsvd2));
	memcpy(dst->rsvd3, info->rsvd3, ARRAY_SIZE(info->rsvd3));
}