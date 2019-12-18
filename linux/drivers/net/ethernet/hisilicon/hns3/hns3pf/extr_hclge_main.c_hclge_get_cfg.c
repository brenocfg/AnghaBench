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
struct hclge_cfg_param_cmd {int /*<<< orphan*/  offset; } ;
struct hclge_cfg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CFG_OFFSET_M ; 
 int /*<<< orphan*/  HCLGE_CFG_OFFSET_S ; 
 unsigned int HCLGE_CFG_RD_LEN_BYTES ; 
 int /*<<< orphan*/  HCLGE_CFG_RD_LEN_M ; 
 int /*<<< orphan*/  HCLGE_CFG_RD_LEN_S ; 
 unsigned int HCLGE_CFG_RD_LEN_UNIT ; 
 int /*<<< orphan*/  HCLGE_OPC_GET_CFG_PARAM ; 
 int HCLGE_PF_CFG_DESC_NUM ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_parse_cfg (struct hclge_cfg*,struct hclge_desc*) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int hclge_get_cfg(struct hclge_dev *hdev, struct hclge_cfg *hcfg)
{
	struct hclge_desc desc[HCLGE_PF_CFG_DESC_NUM];
	struct hclge_cfg_param_cmd *req;
	unsigned int i;
	int ret;

	for (i = 0; i < HCLGE_PF_CFG_DESC_NUM; i++) {
		u32 offset = 0;

		req = (struct hclge_cfg_param_cmd *)desc[i].data;
		hclge_cmd_setup_basic_desc(&desc[i], HCLGE_OPC_GET_CFG_PARAM,
					   true);
		hnae3_set_field(offset, HCLGE_CFG_OFFSET_M,
				HCLGE_CFG_OFFSET_S, i * HCLGE_CFG_RD_LEN_BYTES);
		/* Len should be united by 4 bytes when send to hardware */
		hnae3_set_field(offset, HCLGE_CFG_RD_LEN_M, HCLGE_CFG_RD_LEN_S,
				HCLGE_CFG_RD_LEN_BYTES / HCLGE_CFG_RD_LEN_UNIT);
		req->offset = cpu_to_le32(offset);
	}

	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_PF_CFG_DESC_NUM);
	if (ret) {
		dev_err(&hdev->pdev->dev, "get config failed %d.\n", ret);
		return ret;
	}

	hclge_parse_cfg(hcfg, desc);

	return 0;
}