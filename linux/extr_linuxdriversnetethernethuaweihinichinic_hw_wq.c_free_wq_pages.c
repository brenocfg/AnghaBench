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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_wq {void** shadow_block_vaddr; int /*<<< orphan*/  wq_page_size; int /*<<< orphan*/ * block_vaddr; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  free_wqes_shadow (struct hinic_wq*) ; 

__attribute__((used)) static void free_wq_pages(struct hinic_wq *wq, struct hinic_hwif *hwif,
			  int num_q_pages)
{
	struct pci_dev *pdev = hwif->pdev;
	int i;

	for (i = 0; i < num_q_pages; i++) {
		void **vaddr = &wq->shadow_block_vaddr[i];
		u64 *paddr = &wq->block_vaddr[i];
		dma_addr_t dma_addr;

		dma_addr = (dma_addr_t)be64_to_cpu(*paddr);
		dma_free_coherent(&pdev->dev, wq->wq_page_size, *vaddr,
				  dma_addr);
	}

	free_wqes_shadow(wq);
}