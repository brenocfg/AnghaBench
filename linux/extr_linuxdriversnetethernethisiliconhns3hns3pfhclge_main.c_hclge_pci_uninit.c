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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_base; } ;
struct hclge_dev {TYPE_1__ hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_pci_uninit(struct hclge_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;

	pcim_iounmap(pdev, hdev->hw.io_base);
	pci_free_irq_vectors(pdev);
	pci_clear_master(pdev);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}