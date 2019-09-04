#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hclge_dev {int reset_type; int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CORE_RESET_BIT ; 
 int /*<<< orphan*/  HCLGE_GLOBAL_RESET_BIT ; 
 int /*<<< orphan*/  HCLGE_GLOBAL_RESET_REG ; 
#define  HNAE3_CORE_RESET 130 
#define  HNAE3_FUNC_RESET 129 
#define  HNAE3_GLOBAL_RESET 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hclge_func_reset_cmd (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_reset_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_write_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_do_reset(struct hclge_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	u32 val;

	switch (hdev->reset_type) {
	case HNAE3_GLOBAL_RESET:
		val = hclge_read_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG);
		hnae3_set_bit(val, HCLGE_GLOBAL_RESET_BIT, 1);
		hclge_write_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG, val);
		dev_info(&pdev->dev, "Global Reset requested\n");
		break;
	case HNAE3_CORE_RESET:
		val = hclge_read_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG);
		hnae3_set_bit(val, HCLGE_CORE_RESET_BIT, 1);
		hclge_write_dev(&hdev->hw, HCLGE_GLOBAL_RESET_REG, val);
		dev_info(&pdev->dev, "Core Reset requested\n");
		break;
	case HNAE3_FUNC_RESET:
		dev_info(&pdev->dev, "PF Reset requested\n");
		hclge_func_reset_cmd(hdev, 0);
		/* schedule again to check later */
		set_bit(HNAE3_FUNC_RESET, &hdev->reset_pending);
		hclge_reset_task_schedule(hdev);
		break;
	default:
		dev_warn(&pdev->dev,
			 "Unsupported reset type: %d\n", hdev->reset_type);
		break;
	}
}