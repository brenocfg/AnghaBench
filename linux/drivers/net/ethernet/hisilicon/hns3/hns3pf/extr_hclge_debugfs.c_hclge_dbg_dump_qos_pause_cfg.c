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
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_cfg_pause_param_cmd {int /*<<< orphan*/  pause_trans_time; int /*<<< orphan*/  pause_trans_gap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_CFG_MAC_PARA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_dbg_dump_qos_pause_cfg(struct hclge_dev *hdev)
{
	struct hclge_cfg_pause_param_cmd *pause_param;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_MAC_PARA, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev, "dump checksum fail, ret = %d\n",
			ret);
		return;
	}

	pause_param = (struct hclge_cfg_pause_param_cmd *)desc.data;
	dev_info(&hdev->pdev->dev, "dump qos pause cfg\n");
	dev_info(&hdev->pdev->dev, "pause_trans_gap: 0x%x\n",
		 pause_param->pause_trans_gap);
	dev_info(&hdev->pdev->dev, "pause_trans_time: 0x%x\n",
		 pause_param->pause_trans_time);
}