#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hclge_set_fd_key_config_cmd {int stage; void* meta_data_mask; void* tuple_mask; int /*<<< orphan*/  outer_dipv6_word_en; int /*<<< orphan*/  outer_sipv6_word_en; int /*<<< orphan*/  inner_dipv6_word_en; int /*<<< orphan*/  inner_sipv6_word_en; int /*<<< orphan*/  key_select; } ;
struct hclge_fd_key_cfg {int /*<<< orphan*/  meta_data_active; int /*<<< orphan*/  tuple_active; int /*<<< orphan*/  outer_dipv6_word_en; int /*<<< orphan*/  outer_sipv6_word_en; int /*<<< orphan*/  inner_dipv6_word_en; int /*<<< orphan*/  inner_sipv6_word_en; int /*<<< orphan*/  key_sel; } ;
struct TYPE_3__ {struct hclge_fd_key_cfg* key_cfg; } ;
struct hclge_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; TYPE_1__ fd_cfg; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_FD_KEY_CONFIG ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_fd_key_config(struct hclge_dev *hdev, int stage_num)
{
	struct hclge_set_fd_key_config_cmd *req;
	struct hclge_fd_key_cfg *stage;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_KEY_CONFIG, false);

	req = (struct hclge_set_fd_key_config_cmd *)desc.data;
	stage = &hdev->fd_cfg.key_cfg[stage_num];
	req->stage = stage_num;
	req->key_select = stage->key_sel;
	req->inner_sipv6_word_en = stage->inner_sipv6_word_en;
	req->inner_dipv6_word_en = stage->inner_dipv6_word_en;
	req->outer_sipv6_word_en = stage->outer_sipv6_word_en;
	req->outer_dipv6_word_en = stage->outer_dipv6_word_en;
	req->tuple_mask = cpu_to_le32(~stage->tuple_active);
	req->meta_data_mask = cpu_to_le32(~stage->meta_data_active);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev, "set fd key fail, ret=%d\n", ret);

	return ret;
}