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
struct hinic_wqs {int /*<<< orphan*/ * shadow_page_vaddr; scalar_t__* page_paddr; int /*<<< orphan*/ * page_vaddr; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WQS_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wqs_free_page(struct hinic_wqs *wqs, int page_idx)
{
	struct hinic_hwif *hwif = wqs->hwif;
	struct pci_dev *pdev = hwif->pdev;

	dma_free_coherent(&pdev->dev, WQS_PAGE_SIZE,
			  wqs->page_vaddr[page_idx],
			  (dma_addr_t)wqs->page_paddr[page_idx]);
	vfree(wqs->shadow_page_vaddr[page_idx]);
}