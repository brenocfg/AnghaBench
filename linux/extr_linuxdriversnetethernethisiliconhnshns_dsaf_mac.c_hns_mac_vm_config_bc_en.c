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
typedef  size_t u32 ;
struct mac_entry_idx {int /*<<< orphan*/  vlan_id; } ;
struct hns_mac_cb {scalar_t__ mac_type; int /*<<< orphan*/  mac_id; struct mac_entry_idx* addr_entry_idx; struct dsaf_device* dsaf_dev; } ;
struct dsaf_drv_mac_single_dest_entry {int /*<<< orphan*/  port_num; int /*<<< orphan*/  in_port_num; int /*<<< orphan*/  in_vlan_id; int /*<<< orphan*/  addr; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HNAE_PORT_DEBUG ; 
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (struct dsaf_device*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int hns_dsaf_add_mac_mc_port (struct dsaf_device*,struct dsaf_drv_mac_single_dest_entry*) ; 
 int hns_dsaf_del_mac_mc_port (struct dsaf_device*,struct dsaf_drv_mac_single_dest_entry*) ; 
 int hns_mac_get_inner_port_num (struct hns_mac_cb*,size_t,int /*<<< orphan*/ *) ; 

int hns_mac_vm_config_bc_en(struct hns_mac_cb *mac_cb, u32 vmid, bool enable)
{
	int ret;
	struct dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	u8 port_num;
	struct mac_entry_idx *uc_mac_entry;
	struct dsaf_drv_mac_single_dest_entry mac_entry;

	if (mac_cb->mac_type == HNAE_PORT_DEBUG)
		return 0;

	uc_mac_entry = &mac_cb->addr_entry_idx[vmid];

	if (!HNS_DSAF_IS_DEBUG(dsaf_dev))  {
		eth_broadcast_addr(mac_entry.addr);
		mac_entry.in_vlan_id = uc_mac_entry->vlan_id;
		mac_entry.in_port_num = mac_cb->mac_id;
		ret = hns_mac_get_inner_port_num(mac_cb, vmid, &port_num);
		if (ret)
			return ret;
		mac_entry.port_num = port_num;

		if (!enable)
			ret = hns_dsaf_del_mac_mc_port(dsaf_dev, &mac_entry);
		else
			ret = hns_dsaf_add_mac_mc_port(dsaf_dev, &mac_entry);
		return ret;
	}

	return 0;
}