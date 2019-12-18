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
struct hclge_promisc_param {int enable; int /*<<< orphan*/  vf_id; } ;
struct hclge_promisc_cfg_cmd {int flag; int /*<<< orphan*/  vf_id; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_CFG_PROMISC_MODE ; 
 int HCLGE_PROMISC_EN_B ; 
 int HCLGE_PROMISC_RX_EN_B ; 
 int HCLGE_PROMISC_TX_EN_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

int hclge_cmd_set_promisc_mode(struct hclge_dev *hdev,
			       struct hclge_promisc_param *param)
{
	struct hclge_promisc_cfg_cmd *req;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_PROMISC_MODE, false);

	req = (struct hclge_promisc_cfg_cmd *)desc.data;
	req->vf_id = param->vf_id;

	/* HCLGE_PROMISC_TX_EN_B and HCLGE_PROMISC_RX_EN_B are not supported on
	 * pdev revision(0x20), new revision support them. The
	 * value of this two fields will not return error when driver
	 * send command to fireware in revision(0x20).
	 */
	req->flag = (param->enable << HCLGE_PROMISC_EN_B) |
		HCLGE_PROMISC_TX_EN_B | HCLGE_PROMISC_RX_EN_B;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Set promisc mode fail, status is %d.\n", ret);

	return ret;
}