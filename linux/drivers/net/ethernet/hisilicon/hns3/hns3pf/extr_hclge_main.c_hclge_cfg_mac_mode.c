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
struct hclge_config_mac_mode_cmd {int /*<<< orphan*/  txrx_pad_fcs_loop_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_FCS_TX_B ; 
 int /*<<< orphan*/  HCLGE_MAC_PAD_RX_B ; 
 int /*<<< orphan*/  HCLGE_MAC_PAD_TX_B ; 
 int /*<<< orphan*/  HCLGE_MAC_RX_EN_B ; 
 int /*<<< orphan*/  HCLGE_MAC_RX_FCS_B ; 
 int /*<<< orphan*/  HCLGE_MAC_RX_FCS_STRIP_B ; 
 int /*<<< orphan*/  HCLGE_MAC_RX_OVERSIZE_TRUNCATE_B ; 
 int /*<<< orphan*/  HCLGE_MAC_TX_EN_B ; 
 int /*<<< orphan*/  HCLGE_MAC_TX_OVERSIZE_TRUNCATE_B ; 
 int /*<<< orphan*/  HCLGE_MAC_TX_UNDER_MIN_ERR_B ; 
 int /*<<< orphan*/  HCLGE_OPC_CONFIG_MAC_MODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hclge_cfg_mac_mode(struct hclge_dev *hdev, bool enable)
{
	struct hclge_desc desc;
	struct hclge_config_mac_mode_cmd *req =
		(struct hclge_config_mac_mode_cmd *)desc.data;
	u32 loop_en = 0;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAC_MODE, false);

	if (enable) {
		hnae3_set_bit(loop_en, HCLGE_MAC_TX_EN_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_EN_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_PAD_TX_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_PAD_RX_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_FCS_TX_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_FCS_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_FCS_STRIP_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_TX_OVERSIZE_TRUNCATE_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_RX_OVERSIZE_TRUNCATE_B, 1U);
		hnae3_set_bit(loop_en, HCLGE_MAC_TX_UNDER_MIN_ERR_B, 1U);
	}

	req->txrx_pad_fcs_loop_en = cpu_to_le32(loop_en);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"mac enable fail, ret =%d.\n", ret);
}