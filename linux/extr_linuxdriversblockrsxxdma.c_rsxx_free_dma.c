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
struct rsxx_dma_ctrl {TYPE_1__* card; } ;
struct rsxx_dma {scalar_t__ cmd; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HW_CMD_BLK_DISCARD ; 
 scalar_t__ HW_CMD_BLK_WRITE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  get_dma_size (struct rsxx_dma*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rsxx_dma*) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_dma_pool ; 

__attribute__((used)) static void rsxx_free_dma(struct rsxx_dma_ctrl *ctrl, struct rsxx_dma *dma)
{
	if (dma->cmd != HW_CMD_BLK_DISCARD) {
		if (!pci_dma_mapping_error(ctrl->card->dev, dma->dma_addr)) {
			pci_unmap_page(ctrl->card->dev, dma->dma_addr,
				       get_dma_size(dma),
				       dma->cmd == HW_CMD_BLK_WRITE ?
						   PCI_DMA_TODEVICE :
						   PCI_DMA_FROMDEVICE);
		}
	}

	kmem_cache_free(rsxx_dma_pool, dma);
}