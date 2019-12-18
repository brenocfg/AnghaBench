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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_vport {int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_mac_vlan_tbl_entry_cmd {int /*<<< orphan*/  egress_port; } ;
struct hclge_dev {unsigned char const* priv_umv_size; TYPE_1__* pdev; } ;
struct hclge_desc {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  HCLGE_MAC_EPORT_VFID_M ; 
 int /*<<< orphan*/  HCLGE_MAC_EPORT_VFID_S ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char const*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned char const*) ; 
 int hclge_add_mac_vlan_tbl (struct hclge_vport*,struct hclge_mac_vlan_tbl_entry_cmd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_is_umv_space_full (struct hclge_vport*) ; 
 int hclge_lookup_mac_vlan_tbl (struct hclge_vport*,struct hclge_mac_vlan_tbl_entry_cmd*,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_prepare_mac_addr (struct hclge_mac_vlan_tbl_entry_cmd*,unsigned char const*,int) ; 
 int /*<<< orphan*/  hclge_update_umv_space (struct hclge_vport*,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_zero_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  memset (struct hclge_mac_vlan_tbl_entry_cmd*,int /*<<< orphan*/ ,int) ; 

int hclge_add_uc_addr_common(struct hclge_vport *vport,
			     const unsigned char *addr)
{
	struct hclge_dev *hdev = vport->back;
	struct hclge_mac_vlan_tbl_entry_cmd req;
	struct hclge_desc desc;
	u16 egress_port = 0;
	int ret;

	/* mac addr check */
	if (is_zero_ether_addr(addr) ||
	    is_broadcast_ether_addr(addr) ||
	    is_multicast_ether_addr(addr)) {
		dev_err(&hdev->pdev->dev,
			"Set_uc mac err! invalid mac:%pM. is_zero:%d,is_br=%d,is_mul=%d\n",
			 addr, is_zero_ether_addr(addr),
			 is_broadcast_ether_addr(addr),
			 is_multicast_ether_addr(addr));
		return -EINVAL;
	}

	memset(&req, 0, sizeof(req));

	hnae3_set_field(egress_port, HCLGE_MAC_EPORT_VFID_M,
			HCLGE_MAC_EPORT_VFID_S, vport->vport_id);

	req.egress_port = cpu_to_le16(egress_port);

	hclge_prepare_mac_addr(&req, addr, false);

	/* Lookup the mac address in the mac_vlan table, and add
	 * it if the entry is inexistent. Repeated unicast entry
	 * is not allowed in the mac vlan table.
	 */
	ret = hclge_lookup_mac_vlan_tbl(vport, &req, &desc, false);
	if (ret == -ENOENT) {
		if (!hclge_is_umv_space_full(vport)) {
			ret = hclge_add_mac_vlan_tbl(vport, &req, NULL);
			if (!ret)
				hclge_update_umv_space(vport, false);
			return ret;
		}

		dev_err(&hdev->pdev->dev, "UC MAC table full(%u)\n",
			hdev->priv_umv_size);

		return -ENOSPC;
	}

	/* check if we just hit the duplicate */
	if (!ret) {
		dev_warn(&hdev->pdev->dev, "VF %d mac(%pM) exists\n",
			 vport->vport_id, addr);
		return 0;
	}

	dev_err(&hdev->pdev->dev,
		"PF failed to add unicast entry(%pM) in the MAC table\n",
		addr);

	return ret;
}