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
typedef  int u32 ;
struct cobalt {int dma_channels; int pci_32_bit; scalar_t__ first_fifo_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  CAPABILITY_REGISTER ; 
 int /*<<< orphan*/  CS_REG (int) ; 
 int DMA_TYPE_FIFO ; 
 int DONE ; 
 int PCI_64BIT ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_dma_capability (struct cobalt*) ; 

int omni_sg_dma_init(struct cobalt *cobalt)
{
	u32 capa = ioread32(CAPABILITY_REGISTER);
	int i;

	cobalt->first_fifo_channel = 0;
	cobalt->dma_channels = capa & 0xf;
	if (capa & PCI_64BIT)
		cobalt->pci_32_bit = false;
	else
		cobalt->pci_32_bit = true;

	for (i = 0; i < cobalt->dma_channels; i++) {
		u32 status = ioread32(CS_REG(i));
		u32 ctrl = ioread32(CS_REG(i));

		if (!(ctrl & DONE))
			iowrite32(ABORT, CS_REG(i));

		if (!(status & DMA_TYPE_FIFO))
			cobalt->first_fifo_channel++;
	}
	show_dma_capability(cobalt);
	return 0;
}