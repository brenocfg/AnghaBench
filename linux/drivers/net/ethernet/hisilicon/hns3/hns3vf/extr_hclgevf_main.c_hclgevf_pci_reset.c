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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hclgevf_dev {scalar_t__ reset_type; int /*<<< orphan*/  state; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_IRQ_INITED ; 
 scalar_t__ HNAE3_VF_FULL_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_init_msi (struct hclgevf_dev*) ; 
 int hclgevf_misc_irq_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_misc_irq_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_uninit_msi (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_pci_reset(struct hclgevf_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	int ret = 0;

	if (hdev->reset_type == HNAE3_VF_FULL_RESET &&
	    test_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state)) {
		hclgevf_misc_irq_uninit(hdev);
		hclgevf_uninit_msi(hdev);
		clear_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);
	}

	if (!test_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state)) {
		pci_set_master(pdev);
		ret = hclgevf_init_msi(hdev);
		if (ret) {
			dev_err(&pdev->dev,
				"failed(%d) to init MSI/MSI-X\n", ret);
			return ret;
		}

		ret = hclgevf_misc_irq_init(hdev);
		if (ret) {
			hclgevf_uninit_msi(hdev);
			dev_err(&pdev->dev, "failed(%d) to init Misc IRQ(vector0)\n",
				ret);
			return ret;
		}

		set_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);
	}

	return ret;
}