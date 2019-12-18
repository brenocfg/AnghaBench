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
struct hclge_vlan_filter_pf_cfg_cmd {size_t vlan_offset; int vlan_cfg; size_t* vlan_offset_bitmap; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_VLAN_FILTER_PF_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_port_vlan_filter(struct hclge_dev *hdev, __be16 proto,
				      u16 vlan_id, bool is_kill)
{
	struct hclge_vlan_filter_pf_cfg_cmd *req;
	struct hclge_desc desc;
	u8 vlan_offset_byte_val;
	u8 vlan_offset_byte;
	u8 vlan_offset_160;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_VLAN_FILTER_PF_CFG, false);

	vlan_offset_160 = vlan_id / 160;
	vlan_offset_byte = (vlan_id % 160) / 8;
	vlan_offset_byte_val = 1 << (vlan_id % 8);

	req = (struct hclge_vlan_filter_pf_cfg_cmd *)desc.data;
	req->vlan_offset = vlan_offset_160;
	req->vlan_cfg = is_kill;
	req->vlan_offset_bitmap[vlan_offset_byte] = vlan_offset_byte_val;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"port vlan command, send fail, ret =%d.\n", ret);
	return ret;
}