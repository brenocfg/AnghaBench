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
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_cfg_func_mta_filter_cmd {int /*<<< orphan*/  function_id; int /*<<< orphan*/  accept; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CFG_FUNC_MTA_ACCEPT_B ; 
 int /*<<< orphan*/  HCLGE_OPC_MTA_MAC_FUNC_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hclge_cfg_func_mta_filter(struct hclge_dev *hdev,
			      u8 func_id,
			      bool enable)
{
	struct hclge_cfg_func_mta_filter_cmd *req;
	struct hclge_desc desc;
	int ret;

	req = (struct hclge_cfg_func_mta_filter_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MTA_MAC_FUNC_CFG, false);

	hnae3_set_bit(req->accept, HCLGE_CFG_FUNC_MTA_ACCEPT_B,
		      enable);
	req->function_id = func_id;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Config func_id enable failed for cmd_send, ret =%d.\n",
			ret);

	return ret;
}