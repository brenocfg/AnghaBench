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
typedef  int u8 ;
typedef  int u16 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
typedef  enum hclge_mac_vlan_tbl_opcode { ____Placeholder_hclge_mac_vlan_tbl_opcode } hclge_mac_vlan_tbl_opcode ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOSPC ; 
 int HCLGE_ADD_MC_OVERFLOW ; 
 int HCLGE_ADD_UC_OVERFLOW ; 
 int HCLGE_MAC_VLAN_ADD ; 
 int HCLGE_MAC_VLAN_LKUP ; 
 int HCLGE_MAC_VLAN_REMOVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int hclge_get_mac_vlan_cmd_status(struct hclge_vport *vport,
					 u16 cmdq_resp, u8  resp_code,
					 enum hclge_mac_vlan_tbl_opcode op)
{
	struct hclge_dev *hdev = vport->back;

	if (cmdq_resp) {
		dev_err(&hdev->pdev->dev,
			"cmdq execute failed for get_mac_vlan_cmd_status,status=%d.\n",
			cmdq_resp);
		return -EIO;
	}

	if (op == HCLGE_MAC_VLAN_ADD) {
		if ((!resp_code) || (resp_code == 1)) {
			return 0;
		} else if (resp_code == HCLGE_ADD_UC_OVERFLOW) {
			dev_err(&hdev->pdev->dev,
				"add mac addr failed for uc_overflow.\n");
			return -ENOSPC;
		} else if (resp_code == HCLGE_ADD_MC_OVERFLOW) {
			dev_err(&hdev->pdev->dev,
				"add mac addr failed for mc_overflow.\n");
			return -ENOSPC;
		}

		dev_err(&hdev->pdev->dev,
			"add mac addr failed for undefined, code=%u.\n",
			resp_code);
		return -EIO;
	} else if (op == HCLGE_MAC_VLAN_REMOVE) {
		if (!resp_code) {
			return 0;
		} else if (resp_code == 1) {
			dev_dbg(&hdev->pdev->dev,
				"remove mac addr failed for miss.\n");
			return -ENOENT;
		}

		dev_err(&hdev->pdev->dev,
			"remove mac addr failed for undefined, code=%u.\n",
			resp_code);
		return -EIO;
	} else if (op == HCLGE_MAC_VLAN_LKUP) {
		if (!resp_code) {
			return 0;
		} else if (resp_code == 1) {
			dev_dbg(&hdev->pdev->dev,
				"lookup mac addr failed for miss.\n");
			return -ENOENT;
		}

		dev_err(&hdev->pdev->dev,
			"lookup mac addr failed for undefined, code=%u.\n",
			resp_code);
		return -EIO;
	}

	dev_err(&hdev->pdev->dev,
		"unknown opcode for get_mac_vlan_cmd_status, opcode=%d.\n", op);

	return -EINVAL;
}