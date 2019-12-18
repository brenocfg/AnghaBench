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
struct hinic_wqs {int num_pages; void* page_paddr; void* page_vaddr; void* shadow_page_vaddr; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,void*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_page_arrays(struct hinic_wqs *wqs)
{
	struct hinic_hwif *hwif = wqs->hwif;
	struct pci_dev *pdev = hwif->pdev;
	size_t size;

	size = wqs->num_pages * sizeof(*wqs->page_paddr);
	wqs->page_paddr = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!wqs->page_paddr)
		return -ENOMEM;

	size = wqs->num_pages * sizeof(*wqs->page_vaddr);
	wqs->page_vaddr = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!wqs->page_vaddr)
		goto err_page_vaddr;

	size = wqs->num_pages * sizeof(*wqs->shadow_page_vaddr);
	wqs->shadow_page_vaddr = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!wqs->shadow_page_vaddr)
		goto err_page_shadow_vaddr;

	return 0;

err_page_shadow_vaddr:
	devm_kfree(&pdev->dev, wqs->page_vaddr);

err_page_vaddr:
	devm_kfree(&pdev->dev, wqs->page_paddr);
	return -ENOMEM;
}