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
struct TYPE_3__ {int /*<<< orphan*/  reset_fail_cnt; int /*<<< orphan*/  reset_cnt; int /*<<< orphan*/  hw_reset_done_cnt; int /*<<< orphan*/  reset_done_cnt; int /*<<< orphan*/  imp_rst_cnt; int /*<<< orphan*/  global_rst_cnt; int /*<<< orphan*/  flr_rst_cnt; int /*<<< orphan*/  pf_rst_cnt; } ;
struct hclge_dev {int /*<<< orphan*/  hw; TYPE_2__* pdev; TYPE_1__ rst_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FUN_RST_ING ; 
 int /*<<< orphan*/  HCLGE_GLOBAL_RESET_REG ; 
 int /*<<< orphan*/  HCLGE_MISC_RESET_STS_REG ; 
 int /*<<< orphan*/  HCLGE_MISC_VECTOR_INT_STS ; 
 int /*<<< orphan*/  HCLGE_MISC_VECTOR_REG_BASE ; 
 int /*<<< orphan*/  HCLGE_NIC_CSQ_DEPTH_REG ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_dbg_dump_rst_info(struct hclge_dev *hdev)
{
	dev_info(&hdev->pdev->dev, "PF reset count: %u\n",
		 hdev->rst_stats.pf_rst_cnt);
	dev_info(&hdev->pdev->dev, "FLR reset count: %u\n",
		 hdev->rst_stats.flr_rst_cnt);
	dev_info(&hdev->pdev->dev, "GLOBAL reset count: %u\n",
		 hdev->rst_stats.global_rst_cnt);
	dev_info(&hdev->pdev->dev, "IMP reset count: %u\n",
		 hdev->rst_stats.imp_rst_cnt);
	dev_info(&hdev->pdev->dev, "reset done count: %u\n",
		 hdev->rst_stats.reset_done_cnt);
	dev_info(&hdev->pdev->dev, "HW reset done count: %u\n",
		 hdev->rst_stats.hw_reset_done_cnt);
	dev_info(&hdev->pdev->dev, "reset count: %u\n",
		 hdev->rst_stats.reset_cnt);
	dev_info(&hdev->pdev->dev, "reset count: %u\n",
		 hdev->rst_stats.reset_cnt);
	dev_info(&hdev->pdev->dev, "reset fail count: %u\n",
		 hdev->rst_stats.reset_fail_cnt);
	dev_info(&hdev->pdev->dev, "vector0 interrupt enable status: 0x%x\n",
		 hclge_read_dev(&hdev->hw, HCLGE_MISC_VECTOR_REG_BASE));
	dev_info(&hdev->pdev->dev, "reset interrupt source: 0x%x\n",
		 hclge_read_dev(&hdev->hw, HCLGE_MISC_RESET_STS_REG));
	dev_info(&hdev->pdev->dev, "reset interrupt status: 0x%x\n",
		 hclge_read_dev(&hdev->hw, HCLGE_MISC_VECTOR_INT_STS));
	dev_info(&hdev->pdev->dev, "hardware reset status: 0x%x\n",
		 hclge_read_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG));
	dev_info(&hdev->pdev->dev, "handshake status: 0x%x\n",
		 hclge_read_dev(&hdev->hw, HCLGE_NIC_CSQ_DEPTH_REG));
	dev_info(&hdev->pdev->dev, "function reset status: 0x%x\n",
		 hclge_read_dev(&hdev->hw, HCLGE_FUN_RST_ING));
}