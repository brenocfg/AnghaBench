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
typedef  int uint8_t ;
struct r852_device {scalar_t__ dma_state; int /*<<< orphan*/  phys_dma_addr; int /*<<< orphan*/  phys_bounce_buffer; scalar_t__ dma_dir; } ;

/* Variables and functions */
 scalar_t__ DMA_INTERNAL ; 
 int /*<<< orphan*/  R852_DMA_ADDR ; 
 int R852_DMA_INTERNAL ; 
 int /*<<< orphan*/  R852_DMA_IRQ_ENABLE ; 
 int R852_DMA_IRQ_ERROR ; 
 int R852_DMA_IRQ_INTERNAL ; 
 int R852_DMA_IRQ_MEMORY ; 
 int R852_DMA_MEMORY ; 
 int R852_DMA_READ ; 
 int /*<<< orphan*/  R852_DMA_SETTINGS ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg_dword (struct r852_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r852_dma_enable(struct r852_device *dev)
{
	uint8_t dma_reg, dma_irq_reg;

	/* Set up dma settings */
	dma_reg = r852_read_reg_dword(dev, R852_DMA_SETTINGS);
	dma_reg &= ~(R852_DMA_READ | R852_DMA_INTERNAL | R852_DMA_MEMORY);

	if (dev->dma_dir)
		dma_reg |= R852_DMA_READ;

	if (dev->dma_state == DMA_INTERNAL) {
		dma_reg |= R852_DMA_INTERNAL;
		/* Precaution to make sure HW doesn't write */
			/* to random kernel memory */
		r852_write_reg_dword(dev, R852_DMA_ADDR,
			cpu_to_le32(dev->phys_bounce_buffer));
	} else {
		dma_reg |= R852_DMA_MEMORY;
		r852_write_reg_dword(dev, R852_DMA_ADDR,
			cpu_to_le32(dev->phys_dma_addr));
	}

	/* Precaution: make sure write reached the device */
	r852_read_reg_dword(dev, R852_DMA_ADDR);

	r852_write_reg_dword(dev, R852_DMA_SETTINGS, dma_reg);

	/* Set dma irq */
	dma_irq_reg = r852_read_reg_dword(dev, R852_DMA_IRQ_ENABLE);
	r852_write_reg_dword(dev, R852_DMA_IRQ_ENABLE,
		dma_irq_reg |
		R852_DMA_IRQ_INTERNAL |
		R852_DMA_IRQ_ERROR |
		R852_DMA_IRQ_MEMORY);
}