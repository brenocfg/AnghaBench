#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct dsaf_tbl_tcam_mcast_cfg {int tbl_mcast_item_vld; scalar_t__ tbl_mcast_old_en; int /*<<< orphan*/ * tbl_mcast_port_msk; } ;
struct dsaf_tbl_tcam_data {int /*<<< orphan*/  tbl_tcam_data_low; int /*<<< orphan*/  tbl_tcam_data_high; } ;
struct TYPE_12__ {int /*<<< orphan*/  val; } ;
struct TYPE_9__ {int /*<<< orphan*/  val; } ;
struct dsaf_drv_tbl_tcam_key {TYPE_6__ low; TYPE_3__ high; } ;
struct TYPE_10__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
struct TYPE_11__ {TYPE_4__ low; TYPE_2__ high; } ;
struct dsaf_drv_soft_mac_tbl {TYPE_5__ tcam_key; scalar_t__ index; } ;
struct dsaf_drv_priv {struct dsaf_drv_soft_mac_tbl* soft_mac_tbl; } ;
struct dsaf_drv_mac_single_dest_entry {int in_port_num; int in_vlan_id; int port_num; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct dsaf_device {TYPE_1__ ae_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int DSAF_BASE_INNER_PORT_NUM ; 
 scalar_t__ DSAF_INVALID_ENTRY_IDX ; 
 int DSAF_SERVICE_NW_NUM ; 
 int EINVAL ; 
 int ETH_ALEN ; 
 scalar_t__ MAC_IS_ALL_ZEROS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dsaf_drv_priv* hns_dsaf_dev_priv (struct dsaf_device*) ; 
 scalar_t__ hns_dsaf_find_empty_mac_entry (struct dsaf_device*) ; 
 scalar_t__ hns_dsaf_find_soft_mac_entry (struct dsaf_device*,struct dsaf_drv_tbl_tcam_key*) ; 
 int /*<<< orphan*/  hns_dsaf_mc_mask_bit_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_dsaf_set_mac_key (struct dsaf_device*,struct dsaf_drv_tbl_tcam_key*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_dsaf_setup_mc_mask (struct dsaf_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tcam_mc_cfg (struct dsaf_device*,scalar_t__,struct dsaf_tbl_tcam_data*,struct dsaf_tbl_tcam_data*,struct dsaf_tbl_tcam_mcast_cfg*) ; 
 int /*<<< orphan*/  hns_dsaf_tcam_mc_get (struct dsaf_device*,scalar_t__,struct dsaf_tbl_tcam_data*,struct dsaf_tbl_tcam_mcast_cfg*) ; 
 int /*<<< orphan*/  memset (struct dsaf_tbl_tcam_mcast_cfg*,int /*<<< orphan*/ ,int) ; 

int hns_dsaf_add_mac_mc_port(struct dsaf_device *dsaf_dev,
			     struct dsaf_drv_mac_single_dest_entry *mac_entry)
{
	u16 entry_index = DSAF_INVALID_ENTRY_IDX;
	struct dsaf_drv_tbl_tcam_key mac_key;
	struct dsaf_drv_tbl_tcam_key mask_key;
	struct dsaf_tbl_tcam_data *pmask_key = NULL;
	struct dsaf_tbl_tcam_mcast_cfg mac_data;
	struct dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	struct dsaf_drv_soft_mac_tbl *soft_mac_entry = priv->soft_mac_tbl;
	struct dsaf_tbl_tcam_data tcam_data;
	u8 mc_addr[ETH_ALEN];
	int mskid;

	/*chechk mac addr */
	if (MAC_IS_ALL_ZEROS(mac_entry->addr)) {
		dev_err(dsaf_dev->dev, "set_entry failed,addr %pM!\n",
			mac_entry->addr);
		return -EINVAL;
	}

	ether_addr_copy(mc_addr, mac_entry->addr);
	if (!AE_IS_VER1(dsaf_dev->dsaf_ver)) {
		u8 mc_mask[ETH_ALEN];

		/* prepare for key data setting */
		hns_dsaf_setup_mc_mask(dsaf_dev, mac_entry->in_port_num,
				       mc_mask, mac_entry->addr);
		hns_dsaf_mc_mask_bit_clear(mc_addr, mc_mask);

		/* config key mask */
		hns_dsaf_set_mac_key(dsaf_dev, &mask_key,
				     0x0,
				     0xff,
				     mc_mask);

		pmask_key = (struct dsaf_tbl_tcam_data *)(&mask_key);
	}

	/*config key */
	hns_dsaf_set_mac_key(
		dsaf_dev, &mac_key, mac_entry->in_vlan_id,
		mac_entry->in_port_num, mc_addr);

	memset(&mac_data, 0, sizeof(struct dsaf_tbl_tcam_mcast_cfg));

	/* check if the tcam is exist */
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	if (entry_index == DSAF_INVALID_ENTRY_IDX) {
		/*if hasnot , find a empty*/
		entry_index = hns_dsaf_find_empty_mac_entry(dsaf_dev);
		if (entry_index == DSAF_INVALID_ENTRY_IDX) {
			/*if hasnot empty, error*/
			dev_err(dsaf_dev->dev,
				"set_uc_entry failed, %s Mac key(%#x:%#x)\n",
				dsaf_dev->ae_dev.name, mac_key.high.val,
				mac_key.low.val);
			return -EINVAL;
		}
	} else {
		/* if exist, add in */
		hns_dsaf_tcam_mc_get(dsaf_dev, entry_index, &tcam_data,
				     &mac_data);
	}

	/* config hardware entry */
	if (mac_entry->port_num < DSAF_SERVICE_NW_NUM) {
		mskid = mac_entry->port_num;
	} else if (mac_entry->port_num >= DSAF_BASE_INNER_PORT_NUM) {
		mskid = mac_entry->port_num -
			DSAF_BASE_INNER_PORT_NUM + DSAF_SERVICE_NW_NUM;
	} else {
		dev_err(dsaf_dev->dev,
			"%s,pnum(%d)error,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, mac_entry->port_num,
			mac_key.high.val, mac_key.low.val);
		return -EINVAL;
	}
	dsaf_set_bit(mac_data.tbl_mcast_port_msk[mskid / 32], mskid % 32, 1);
	mac_data.tbl_mcast_old_en = 0;
	mac_data.tbl_mcast_item_vld = 1;

	dev_dbg(dsaf_dev->dev,
		"set_uc_entry, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	tcam_data.tbl_tcam_data_high = mac_key.high.val;
	tcam_data.tbl_tcam_data_low = mac_key.low.val;

	/* config mc entry with mask */
	hns_dsaf_tcam_mc_cfg(dsaf_dev, entry_index, &tcam_data,
			     pmask_key, &mac_data);

	/*config software entry */
	soft_mac_entry += entry_index;
	soft_mac_entry->index = entry_index;
	soft_mac_entry->tcam_key.high.val = mac_key.high.val;
	soft_mac_entry->tcam_key.low.val = mac_key.low.val;

	return 0;
}