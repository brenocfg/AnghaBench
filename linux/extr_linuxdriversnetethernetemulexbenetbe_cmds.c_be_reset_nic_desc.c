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
struct be_nic_res_desc {int unicast_mac_count; int mcc_count; int vlan_count; int mcast_mac_count; int txq_count; int rq_count; int rssq_count; int lro_count; int cq_count; int toe_conn_count; int eq_count; int iface_count; int link_param; int acpi_params; int wol_param; int tunnel_iface_count; int direct_tenant_iface_count; int bw_min; int bw_max; int /*<<< orphan*/  channel_id_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct be_nic_res_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void be_reset_nic_desc(struct be_nic_res_desc *nic)
{
	memset(nic, 0, sizeof(*nic));
	nic->unicast_mac_count = 0xFFFF;
	nic->mcc_count = 0xFFFF;
	nic->vlan_count = 0xFFFF;
	nic->mcast_mac_count = 0xFFFF;
	nic->txq_count = 0xFFFF;
	nic->rq_count = 0xFFFF;
	nic->rssq_count = 0xFFFF;
	nic->lro_count = 0xFFFF;
	nic->cq_count = 0xFFFF;
	nic->toe_conn_count = 0xFFFF;
	nic->eq_count = 0xFFFF;
	nic->iface_count = 0xFFFF;
	nic->link_param = 0xFF;
	nic->channel_id_param = cpu_to_le16(0xF000);
	nic->acpi_params = 0xFF;
	nic->wol_param = 0x0F;
	nic->tunnel_iface_count = 0xFFFF;
	nic->direct_tenant_iface_count = 0xFFFF;
	nic->bw_min = 0xFFFFFFFF;
	nic->bw_max = 0xFFFFFFFF;
}