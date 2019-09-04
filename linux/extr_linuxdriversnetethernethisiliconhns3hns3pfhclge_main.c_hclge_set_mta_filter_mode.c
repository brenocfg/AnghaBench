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
struct hclge_mta_filter_mode_cmd {int /*<<< orphan*/  dmac_sel_en; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  enum hclge_mta_dmac_sel_type { ____Placeholder_hclge_mta_dmac_sel_type } hclge_mta_dmac_sel_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CFG_MTA_MAC_EN_B ; 
 int /*<<< orphan*/  HCLGE_CFG_MTA_MAC_SEL_M ; 
 int /*<<< orphan*/  HCLGE_CFG_MTA_MAC_SEL_S ; 
 int /*<<< orphan*/  HCLGE_OPC_MTA_MAC_MODE_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_mta_filter_mode(struct hclge_dev *hdev,
				     enum hclge_mta_dmac_sel_type mta_mac_sel,
				     bool enable)
{
	struct hclge_mta_filter_mode_cmd *req;
	struct hclge_desc desc;
	int ret;

	req = (struct hclge_mta_filter_mode_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MTA_MAC_MODE_CFG, false);

	hnae3_set_bit(req->dmac_sel_en, HCLGE_CFG_MTA_MAC_EN_B,
		      enable);
	hnae3_set_field(req->dmac_sel_en, HCLGE_CFG_MTA_MAC_SEL_M,
			HCLGE_CFG_MTA_MAC_SEL_S, mta_mac_sel);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Config mat filter mode failed for cmd_send, ret =%d.\n",
			ret);

	return ret;
}