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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_dev {int reset_type; int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  hw; struct pci_dev* pdev; TYPE_1__* vport; } ;
struct TYPE_2__ {struct hnae3_handle nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FUN_RST_ING ; 
 int /*<<< orphan*/  HCLGE_GLOBAL_RESET_BIT ; 
 int /*<<< orphan*/  HCLGE_GLOBAL_RESET_REG ; 
#define  HNAE3_FLR_RESET 130 
#define  HNAE3_FUNC_RESET 129 
#define  HNAE3_GLOBAL_RESET 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ hclge_get_hw_reset_stat (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_reset_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_write_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_do_reset(struct hclge_dev *hdev)
{
	struct hnae3_handle *handle = &hdev->vport[0].nic;
	struct pci_dev *pdev = hdev->pdev;
	u32 val;

	if (hclge_get_hw_reset_stat(handle)) {
		dev_info(&pdev->dev, "Hardware reset not finish\n");
		dev_info(&pdev->dev, "func_rst_reg:0x%x, global_rst_reg:0x%x\n",
			 hclge_read_dev(&hdev->hw, HCLGE_FUN_RST_ING),
			 hclge_read_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG));
		return;
	}

	switch (hdev->reset_type) {
	case HNAE3_GLOBAL_RESET:
		val = hclge_read_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG);
		hnae3_set_bit(val, HCLGE_GLOBAL_RESET_BIT, 1);
		hclge_write_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG, val);
		dev_info(&pdev->dev, "Global Reset requested\n");
		break;
	case HNAE3_FUNC_RESET:
		dev_info(&pdev->dev, "PF Reset requested\n");
		/* schedule again to check later */
		set_bit(HNAE3_FUNC_RESET, &hdev->reset_pending);
		hclge_reset_task_schedule(hdev);
		break;
	case HNAE3_FLR_RESET:
		dev_info(&pdev->dev, "FLR requested\n");
		/* schedule again to check later */
		set_bit(HNAE3_FLR_RESET, &hdev->reset_pending);
		hclge_reset_task_schedule(hdev);
		break;
	default:
		dev_warn(&pdev->dev,
			 "Unsupported reset type: %d\n", hdev->reset_type);
		break;
	}
}