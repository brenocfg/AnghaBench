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
typedef  scalar_t__ u32 ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_OPC_QUERY_REG_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_get_regs_num(struct hclge_dev *hdev, u32 *regs_num_32_bit,
			      u32 *regs_num_64_bit)
{
	struct hclge_desc desc;
	u32 total_num;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_REG_NUM, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Query register number cmd failed, ret = %d.\n", ret);
		return ret;
	}

	*regs_num_32_bit = le32_to_cpu(desc.data[0]);
	*regs_num_64_bit = le32_to_cpu(desc.data[1]);

	total_num = *regs_num_32_bit + *regs_num_64_bit;
	if (!total_num)
		return -EINVAL;

	return 0;
}