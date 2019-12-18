#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct dsaf_tbl_tcam_ucast_cfg {scalar_t__ tbl_ucast_out_port; } ;
struct dsaf_tbl_tcam_data {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct dsaf_drv_tbl_tcam_key {TYPE_3__ low; TYPE_2__ high; } ;
struct dsaf_drv_mac_single_dest_entry {scalar_t__ port_num; int /*<<< orphan*/  addr; int /*<<< orphan*/  in_port_num; int /*<<< orphan*/  in_vlan_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct dsaf_device {TYPE_1__ ae_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DSAF_INVALID_ENTRY_IDX ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_dsaf_del_mac_entry (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hns_dsaf_find_soft_mac_entry (struct dsaf_device*,struct dsaf_drv_tbl_tcam_key*) ; 
 int /*<<< orphan*/  hns_dsaf_set_mac_key (struct dsaf_device*,struct dsaf_drv_tbl_tcam_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tcam_uc_get (struct dsaf_device*,scalar_t__,struct dsaf_tbl_tcam_data*,struct dsaf_tbl_tcam_ucast_cfg*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 

int hns_dsaf_rm_mac_addr(
	struct dsaf_device *dsaf_dev,
	struct dsaf_drv_mac_single_dest_entry *mac_entry)
{
	u16 entry_index = DSAF_INVALID_ENTRY_IDX;
	struct dsaf_tbl_tcam_ucast_cfg mac_data;
	struct dsaf_drv_tbl_tcam_key mac_key;

	/* mac addr check */
	if (!is_valid_ether_addr(mac_entry->addr)) {
		dev_err(dsaf_dev->dev, "rm_uc_addr %s Mac %pM err!\n",
			dsaf_dev->ae_dev.name, mac_entry->addr);
		return -EINVAL;
	}

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, mac_entry->in_vlan_id,
			     mac_entry->in_port_num, mac_entry->addr);

	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	if (entry_index == DSAF_INVALID_ENTRY_IDX) {
		/* can not find the tcam entry, return 0 */
		dev_info(dsaf_dev->dev,
			 "rm_uc_addr no tcam, %s Mac key(%#x:%#x)\n",
			 dsaf_dev->ae_dev.name,
			 mac_key.high.val, mac_key.low.val);
		return 0;
	}

	dev_dbg(dsaf_dev->dev,
		"rm_uc_addr, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	hns_dsaf_tcam_uc_get(
			dsaf_dev, entry_index,
			(struct dsaf_tbl_tcam_data *)&mac_key,
			&mac_data);

	/* unicast entry not used locally should not clear */
	if (mac_entry->port_num != mac_data.tbl_ucast_out_port)
		return -EFAULT;

	return hns_dsaf_del_mac_entry(dsaf_dev,
				      mac_entry->in_vlan_id,
				      mac_entry->in_port_num,
				      mac_entry->addr);
}