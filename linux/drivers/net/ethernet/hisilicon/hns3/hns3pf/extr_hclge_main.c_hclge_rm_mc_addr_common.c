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
struct hclge_vport {int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_mac_vlan_tbl_entry_cmd {int /*<<< orphan*/  entry_type; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct hclge_desc {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
typedef  enum hclge_cmd_status { ____Placeholder_hclge_cmd_status } hclge_cmd_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_MAC_VLAN_BIT0_EN_B ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char const*) ; 
 int hclge_add_mac_vlan_tbl (struct hclge_vport*,struct hclge_mac_vlan_tbl_entry_cmd*,struct hclge_desc*) ; 
 scalar_t__ hclge_is_all_function_id_zero (struct hclge_desc*) ; 
 int hclge_lookup_mac_vlan_tbl (struct hclge_vport*,struct hclge_mac_vlan_tbl_entry_cmd*,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_prepare_mac_addr (struct hclge_mac_vlan_tbl_entry_cmd*,unsigned char const*,int) ; 
 int hclge_remove_mac_vlan_tbl (struct hclge_vport*,struct hclge_mac_vlan_tbl_entry_cmd*) ; 
 int hclge_update_desc_vfid (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  memset (struct hclge_mac_vlan_tbl_entry_cmd*,int /*<<< orphan*/ ,int) ; 

int hclge_rm_mc_addr_common(struct hclge_vport *vport,
			    const unsigned char *addr)
{
	struct hclge_dev *hdev = vport->back;
	struct hclge_mac_vlan_tbl_entry_cmd req;
	enum hclge_cmd_status status;
	struct hclge_desc desc[3];

	/* mac addr check */
	if (!is_multicast_ether_addr(addr)) {
		dev_dbg(&hdev->pdev->dev,
			"Remove mc mac err! invalid mac:%pM.\n",
			 addr);
		return -EINVAL;
	}

	memset(&req, 0, sizeof(req));
	hnae3_set_bit(req.entry_type, HCLGE_MAC_VLAN_BIT0_EN_B, 0);
	hclge_prepare_mac_addr(&req, addr, true);
	status = hclge_lookup_mac_vlan_tbl(vport, &req, desc, true);
	if (!status) {
		/* This mac addr exist, remove this handle's VFID for it */
		status = hclge_update_desc_vfid(desc, vport->vport_id, true);
		if (status)
			return status;

		if (hclge_is_all_function_id_zero(desc))
			/* All the vfid is zero, so need to delete this entry */
			status = hclge_remove_mac_vlan_tbl(vport, &req);
		else
			/* Not all the vfid is zero, update the vfid */
			status = hclge_add_mac_vlan_tbl(vport, &req, desc);

	} else {
		/* Maybe this mac address is in mta table, but it cannot be
		 * deleted here because an entry of mta represents an address
		 * range rather than a specific address. the delete action to
		 * all entries will take effect in update_mta_status called by
		 * hns3_nic_set_rx_mode.
		 */
		status = 0;
	}

	return status;
}