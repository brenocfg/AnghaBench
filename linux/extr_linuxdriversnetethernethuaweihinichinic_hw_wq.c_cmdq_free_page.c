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
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_cmdq_pages {int /*<<< orphan*/  shadow_page_vaddr; scalar_t__ page_paddr; int /*<<< orphan*/  page_vaddr; struct hinic_hwif* hwif; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmdq_free_page(struct hinic_cmdq_pages *cmdq_pages)
{
	struct hinic_hwif *hwif = cmdq_pages->hwif;
	struct pci_dev *pdev = hwif->pdev;

	dma_free_coherent(&pdev->dev, CMDQ_PAGE_SIZE,
			  cmdq_pages->page_vaddr,
			  (dma_addr_t)cmdq_pages->page_paddr);
	vfree(cmdq_pages->shadow_page_vaddr);
}