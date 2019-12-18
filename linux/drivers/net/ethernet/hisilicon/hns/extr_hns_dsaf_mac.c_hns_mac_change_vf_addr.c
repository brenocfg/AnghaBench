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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct mac_entry_idx {int valid; int /*<<< orphan*/  addr; int /*<<< orphan*/  vlan_id; } ;
struct mac_driver {int /*<<< orphan*/  (* set_mac_addr ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;
struct hns_mac_cb {TYPE_1__ priv; int /*<<< orphan*/  mac_id; struct mac_entry_idx* addr_entry_idx; struct dsaf_device* dsaf_dev; } ;
struct dsaf_drv_mac_single_dest_entry {int /*<<< orphan*/  port_num; int /*<<< orphan*/  in_port_num; int /*<<< orphan*/  in_vlan_id; int /*<<< orphan*/  addr; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (struct dsaf_device*) ; 
 int hns_dsaf_del_mac_entry (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_dsaf_set_mac_uc_entry (struct dsaf_device*,struct dsaf_drv_mac_single_dest_entry*) ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int hns_mac_get_inner_port_num (struct hns_mac_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

int hns_mac_change_vf_addr(struct hns_mac_cb *mac_cb,
			   u32 vmid, char *addr)
{
	int ret;
	struct mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);
	struct dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	struct dsaf_drv_mac_single_dest_entry mac_entry;
	struct mac_entry_idx *old_entry;

	old_entry = &mac_cb->addr_entry_idx[vmid];
	if (!HNS_DSAF_IS_DEBUG(dsaf_dev)) {
		memcpy(mac_entry.addr, addr, sizeof(mac_entry.addr));
		mac_entry.in_vlan_id = old_entry->vlan_id;
		mac_entry.in_port_num = mac_cb->mac_id;
		ret = hns_mac_get_inner_port_num(mac_cb, (u8)vmid,
						 &mac_entry.port_num);
		if (ret)
			return ret;

		if ((old_entry->valid != 0) &&
		    (memcmp(old_entry->addr,
		    addr, sizeof(mac_entry.addr)) != 0)) {
			ret = hns_dsaf_del_mac_entry(dsaf_dev,
						     old_entry->vlan_id,
						     mac_cb->mac_id,
						     old_entry->addr);
			if (ret)
				return ret;
		}

		ret = hns_dsaf_set_mac_uc_entry(dsaf_dev, &mac_entry);
		if (ret)
			return ret;
	}

	if ((mac_ctrl_drv->set_mac_addr) && (vmid == 0))
		mac_ctrl_drv->set_mac_addr(mac_cb->priv.mac, addr);

	memcpy(old_entry->addr, addr, sizeof(old_entry->addr));
	old_entry->valid = 1;
	return 0;
}