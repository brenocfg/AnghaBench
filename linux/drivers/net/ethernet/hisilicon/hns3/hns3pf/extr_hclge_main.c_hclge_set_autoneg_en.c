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
typedef  int /*<<< orphan*/  u32 ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_config_auto_neg_cmd {int /*<<< orphan*/  cfg_an_cmd_flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_CFG_AN_EN_B ; 
 int /*<<< orphan*/  HCLGE_OPC_CONFIG_AN_MODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int hclge_set_autoneg_en(struct hclge_dev *hdev, bool enable)
{
	struct hclge_config_auto_neg_cmd *req;
	struct hclge_desc desc;
	u32 flag = 0;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_AN_MODE, false);

	req = (struct hclge_config_auto_neg_cmd *)desc.data;
	if (enable)
		hnae3_set_bit(flag, HCLGE_MAC_CFG_AN_EN_B, 1U);
	req->cfg_an_cmd_flag = cpu_to_le32(flag);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev, "auto neg set cmd failed %d.\n",
			ret);

	return ret;
}