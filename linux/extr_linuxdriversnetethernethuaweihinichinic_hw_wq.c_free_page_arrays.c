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
struct hinic_wqs {int /*<<< orphan*/  page_paddr; int /*<<< orphan*/  page_vaddr; int /*<<< orphan*/  shadow_page_vaddr; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_page_arrays(struct hinic_wqs *wqs)
{
	struct hinic_hwif *hwif = wqs->hwif;
	struct pci_dev *pdev = hwif->pdev;

	devm_kfree(&pdev->dev, wqs->shadow_page_vaddr);
	devm_kfree(&pdev->dev, wqs->page_vaddr);
	devm_kfree(&pdev->dev, wqs->page_paddr);
}