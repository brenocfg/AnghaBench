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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_get_fd_allocation_cmd {int /*<<< orphan*/  stage2_counter_num; int /*<<< orphan*/  stage1_counter_num; int /*<<< orphan*/  stage2_entry_num; int /*<<< orphan*/  stage1_entry_num; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_FD_GET_ALLOCATION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_get_fd_allocation(struct hclge_dev *hdev,
				   u32 *stage1_entry_num,
				   u32 *stage2_entry_num,
				   u16 *stage1_counter_num,
				   u16 *stage2_counter_num)
{
	struct hclge_get_fd_allocation_cmd *req;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_FD_GET_ALLOCATION, true);

	req = (struct hclge_get_fd_allocation_cmd *)desc.data;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev, "query fd allocation fail, ret=%d\n",
			ret);
		return ret;
	}

	*stage1_entry_num = le32_to_cpu(req->stage1_entry_num);
	*stage2_entry_num = le32_to_cpu(req->stage2_entry_num);
	*stage1_counter_num = le16_to_cpu(req->stage1_counter_num);
	*stage2_counter_num = le16_to_cpu(req->stage2_counter_num);

	return ret;
}