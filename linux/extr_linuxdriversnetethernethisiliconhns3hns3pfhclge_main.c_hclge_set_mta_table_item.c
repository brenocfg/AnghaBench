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
struct hclge_vport {int /*<<< orphan*/  mta_shadow; struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_cfg_func_mta_item_cmd {int /*<<< orphan*/  item_idx; int /*<<< orphan*/  accept; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CFG_MTA_ITEM_ACCEPT_B ; 
 int /*<<< orphan*/  HCLGE_CFG_MTA_ITEM_IDX_M ; 
 int /*<<< orphan*/  HCLGE_CFG_MTA_ITEM_IDX_S ; 
 int /*<<< orphan*/  HCLGE_OPC_MTA_TBL_ITEM_CFG ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_mta_table_item(struct hclge_vport *vport,
				    u16 idx,
				    bool enable)
{
	struct hclge_dev *hdev = vport->back;
	struct hclge_cfg_func_mta_item_cmd *req;
	struct hclge_desc desc;
	u16 item_idx = 0;
	int ret;

	req = (struct hclge_cfg_func_mta_item_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MTA_TBL_ITEM_CFG, false);
	hnae3_set_bit(req->accept, HCLGE_CFG_MTA_ITEM_ACCEPT_B, enable);

	hnae3_set_field(item_idx, HCLGE_CFG_MTA_ITEM_IDX_M,
			HCLGE_CFG_MTA_ITEM_IDX_S, idx);
	req->item_idx = cpu_to_le16(item_idx);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Config mta table item failed for cmd_send, ret =%d.\n",
			ret);
		return ret;
	}

	if (enable)
		set_bit(idx, vport->mta_shadow);
	else
		clear_bit(idx, vport->mta_shadow);

	return 0;
}