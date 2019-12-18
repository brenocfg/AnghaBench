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
struct hclge_desc {int /*<<< orphan*/  flag; } ;
typedef  enum hclge_opcode_type { ____Placeholder_hclge_opcode_type } hclge_opcode_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CMD_FLAG_NEXT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int,int) ; 

__attribute__((used)) static int hclge_dfx_reg_cmd_send(struct hclge_dev *hdev,
				  struct hclge_desc *desc_src, int bd_num,
				  enum hclge_opcode_type cmd)
{
	struct hclge_desc *desc = desc_src;
	int i, ret;

	hclge_cmd_setup_basic_desc(desc, cmd, true);
	for (i = 0; i < bd_num - 1; i++) {
		desc->flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
		desc++;
		hclge_cmd_setup_basic_desc(desc, cmd, true);
	}

	desc = desc_src;
	ret = hclge_cmd_send(&hdev->hw, desc, bd_num);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Query dfx reg cmd(0x%x) send fail, status is %d.\n",
			cmd, ret);

	return ret;
}