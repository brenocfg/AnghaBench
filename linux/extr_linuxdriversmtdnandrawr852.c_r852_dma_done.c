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
struct r852_device {scalar_t__ dma_stage; scalar_t__ phys_bounce_buffer; int dma_error; scalar_t__ phys_dma_addr; scalar_t__ dma_dir; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  R852_DMA_ADDR ; 
 int /*<<< orphan*/  R852_DMA_IRQ_ENABLE ; 
 int /*<<< orphan*/  R852_DMA_IRQ_STA ; 
 int /*<<< orphan*/  R852_DMA_LEN ; 
 int /*<<< orphan*/  R852_DMA_SETTINGS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg_dword (struct r852_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r852_dma_done(struct r852_device *dev, int error)
{
	WARN_ON(dev->dma_stage == 0);

	r852_write_reg_dword(dev, R852_DMA_IRQ_STA,
			r852_read_reg_dword(dev, R852_DMA_IRQ_STA));

	r852_write_reg_dword(dev, R852_DMA_SETTINGS, 0);
	r852_write_reg_dword(dev, R852_DMA_IRQ_ENABLE, 0);

	/* Precaution to make sure HW doesn't write to random kernel memory */
	r852_write_reg_dword(dev, R852_DMA_ADDR,
		cpu_to_le32(dev->phys_bounce_buffer));
	r852_read_reg_dword(dev, R852_DMA_ADDR);

	dev->dma_error = error;
	dev->dma_stage = 0;

	if (dev->phys_dma_addr && dev->phys_dma_addr != dev->phys_bounce_buffer)
		pci_unmap_single(dev->pci_dev, dev->phys_dma_addr, R852_DMA_LEN,
			dev->dma_dir ? PCI_DMA_FROMDEVICE : PCI_DMA_TODEVICE);
}