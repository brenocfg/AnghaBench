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
typedef  scalar_t__ u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,scalar_t__*,scalar_t__) ; 
 void** vzalloc (size_t) ; 

__attribute__((used)) static int queue_alloc_page(struct hinic_hwif *hwif, u64 **vaddr, u64 *paddr,
			    void ***shadow_vaddr, size_t page_sz)
{
	struct pci_dev *pdev = hwif->pdev;
	dma_addr_t dma_addr;

	*vaddr = dma_alloc_coherent(&pdev->dev, page_sz, &dma_addr,
				    GFP_KERNEL);
	if (!*vaddr) {
		dev_err(&pdev->dev, "Failed to allocate dma for wqs page\n");
		return -ENOMEM;
	}

	*paddr = (u64)dma_addr;

	/* use vzalloc for big mem */
	*shadow_vaddr = vzalloc(page_sz);
	if (!*shadow_vaddr)
		goto err_shadow_vaddr;

	return 0;

err_shadow_vaddr:
	dma_free_coherent(&pdev->dev, page_sz, *vaddr, dma_addr);
	return -ENOMEM;
}