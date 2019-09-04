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
struct pluto {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  TS_DMA_BYTES ; 
 int pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pluto_dma_map(struct pluto *pluto)
{
	pluto->dma_addr = pci_map_single(pluto->pdev, pluto->dma_buf,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);

	return pci_dma_mapping_error(pluto->pdev, pluto->dma_addr);
}