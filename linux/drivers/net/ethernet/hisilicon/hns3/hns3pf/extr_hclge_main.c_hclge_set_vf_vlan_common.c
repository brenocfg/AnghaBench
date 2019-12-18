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
typedef  size_t u8 ;
typedef  int u16 ;
struct hclge_vlan_filter_vf_cfg_cmd {int vlan_cfg; size_t* vf_bitmap; int resp_code; int /*<<< orphan*/  vlan_id; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  vf_vlan_full; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; int /*<<< orphan*/  flag; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int HCLGE_CMD_FLAG_NEXT ; 
 size_t HCLGE_MAX_VF_BYTES ; 
 int /*<<< orphan*/  HCLGE_OPC_VLAN_FILTER_VF_CFG ; 
 int HCLGE_VF_VLAN_DEL_NO_FOUND ; 
 int HCLGE_VF_VLAN_NO_ENTRY ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_vf_vlan_common(struct hclge_dev *hdev, u16 vfid,
				    bool is_kill, u16 vlan,
				    __be16 proto)
{
#define HCLGE_MAX_VF_BYTES  16
	struct hclge_vlan_filter_vf_cfg_cmd *req0;
	struct hclge_vlan_filter_vf_cfg_cmd *req1;
	struct hclge_desc desc[2];
	u8 vf_byte_val;
	u8 vf_byte_off;
	int ret;

	/* if vf vlan table is full, firmware will close vf vlan filter, it
	 * is unable and unnecessary to add new vlan id to vf vlan filter
	 */
	if (test_bit(vfid, hdev->vf_vlan_full) && !is_kill)
		return 0;

	hclge_cmd_setup_basic_desc(&desc[0],
				   HCLGE_OPC_VLAN_FILTER_VF_CFG, false);
	hclge_cmd_setup_basic_desc(&desc[1],
				   HCLGE_OPC_VLAN_FILTER_VF_CFG, false);

	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);

	vf_byte_off = vfid / 8;
	vf_byte_val = 1 << (vfid % 8);

	req0 = (struct hclge_vlan_filter_vf_cfg_cmd *)desc[0].data;
	req1 = (struct hclge_vlan_filter_vf_cfg_cmd *)desc[1].data;

	req0->vlan_id  = cpu_to_le16(vlan);
	req0->vlan_cfg = is_kill;

	if (vf_byte_off < HCLGE_MAX_VF_BYTES)
		req0->vf_bitmap[vf_byte_off] = vf_byte_val;
	else
		req1->vf_bitmap[vf_byte_off - HCLGE_MAX_VF_BYTES] = vf_byte_val;

	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Send vf vlan command fail, ret =%d.\n",
			ret);
		return ret;
	}

	if (!is_kill) {
#define HCLGE_VF_VLAN_NO_ENTRY	2
		if (!req0->resp_code || req0->resp_code == 1)
			return 0;

		if (req0->resp_code == HCLGE_VF_VLAN_NO_ENTRY) {
			set_bit(vfid, hdev->vf_vlan_full);
			dev_warn(&hdev->pdev->dev,
				 "vf vlan table is full, vf vlan filter is disabled\n");
			return 0;
		}

		dev_err(&hdev->pdev->dev,
			"Add vf vlan filter fail, ret =%d.\n",
			req0->resp_code);
	} else {
#define HCLGE_VF_VLAN_DEL_NO_FOUND	1
		if (!req0->resp_code)
			return 0;

		/* vf vlan filter is disabled when vf vlan table is full,
		 * then new vlan id will not be added into vf vlan table.
		 * Just return 0 without warning, avoid massive verbose
		 * print logs when unload.
		 */
		if (req0->resp_code == HCLGE_VF_VLAN_DEL_NO_FOUND)
			return 0;

		dev_err(&hdev->pdev->dev,
			"Kill vf vlan filter fail, ret =%d.\n",
			req0->resp_code);
	}

	return -EIO;
}