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
typedef  int u32 ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_config_fec_cmd {int /*<<< orphan*/  fec_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCLGE_MAC_CFG_FEC_AUTO_EN_B ; 
 int /*<<< orphan*/  HCLGE_MAC_CFG_FEC_MODE_M ; 
 int /*<<< orphan*/  HCLGE_MAC_CFG_FEC_MODE_S ; 
 int /*<<< orphan*/  HCLGE_MAC_FEC_BASER ; 
 int /*<<< orphan*/  HCLGE_MAC_FEC_RS ; 
 int /*<<< orphan*/  HCLGE_OPC_CONFIG_FEC_MODE ; 
 int /*<<< orphan*/  HNAE3_FEC_AUTO ; 
 int /*<<< orphan*/  HNAE3_FEC_BASER ; 
 int /*<<< orphan*/  HNAE3_FEC_RS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_fec_hw(struct hclge_dev *hdev, u32 fec_mode)
{
	struct hclge_config_fec_cmd *req;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_FEC_MODE, false);

	req = (struct hclge_config_fec_cmd *)desc.data;
	if (fec_mode & BIT(HNAE3_FEC_AUTO))
		hnae3_set_bit(req->fec_mode, HCLGE_MAC_CFG_FEC_AUTO_EN_B, 1);
	if (fec_mode & BIT(HNAE3_FEC_RS))
		hnae3_set_field(req->fec_mode, HCLGE_MAC_CFG_FEC_MODE_M,
				HCLGE_MAC_CFG_FEC_MODE_S, HCLGE_MAC_FEC_RS);
	if (fec_mode & BIT(HNAE3_FEC_BASER))
		hnae3_set_field(req->fec_mode, HCLGE_MAC_CFG_FEC_MODE_M,
				HCLGE_MAC_CFG_FEC_MODE_S, HCLGE_MAC_FEC_BASER);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev, "set fec mode failed %d.\n", ret);

	return ret;
}