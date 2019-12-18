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
struct hclgevf_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_IRQ_INITED ; 
 int /*<<< orphan*/  hclgevf_cmd_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_misc_irq_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_pci_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_state_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_uninit_msi (struct hclgevf_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclgevf_uninit_hdev(struct hclgevf_dev *hdev)
{
	hclgevf_state_uninit(hdev);

	if (test_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state)) {
		hclgevf_misc_irq_uninit(hdev);
		hclgevf_uninit_msi(hdev);
	}

	hclgevf_pci_uninit(hdev);
	hclgevf_cmd_uninit(hdev);
}