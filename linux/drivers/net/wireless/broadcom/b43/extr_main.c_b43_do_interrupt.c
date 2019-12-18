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
struct b43_wldev {int irq_mask; int* dma_reason; int irq_reason; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_DMA0_REASON ; 
 int /*<<< orphan*/  B43_MMIO_DMA1_REASON ; 
 int /*<<< orphan*/  B43_MMIO_DMA2_REASON ; 
 int /*<<< orphan*/  B43_MMIO_DMA3_REASON ; 
 int /*<<< orphan*/  B43_MMIO_DMA4_REASON ; 
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_MASK ; 
 int /*<<< orphan*/  B43_MMIO_GEN_IRQ_REASON ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t b43_do_interrupt(struct b43_wldev *dev)
{
	u32 reason;

	/* This code runs under wl->hardirq_lock, but _only_ on non-SDIO busses.
	 * On SDIO, this runs under wl->mutex. */

	reason = b43_read32(dev, B43_MMIO_GEN_IRQ_REASON);
	if (reason == 0xffffffff)	/* shared IRQ */
		return IRQ_NONE;
	reason &= dev->irq_mask;
	if (!reason)
		return IRQ_NONE;

	dev->dma_reason[0] = b43_read32(dev, B43_MMIO_DMA0_REASON)
	    & 0x0001FC00;
	dev->dma_reason[1] = b43_read32(dev, B43_MMIO_DMA1_REASON)
	    & 0x0000DC00;
	dev->dma_reason[2] = b43_read32(dev, B43_MMIO_DMA2_REASON)
	    & 0x0000DC00;
	dev->dma_reason[3] = b43_read32(dev, B43_MMIO_DMA3_REASON)
	    & 0x0001DC00;
	dev->dma_reason[4] = b43_read32(dev, B43_MMIO_DMA4_REASON)
	    & 0x0000DC00;
/* Unused ring
	dev->dma_reason[5] = b43_read32(dev, B43_MMIO_DMA5_REASON)
	    & 0x0000DC00;
*/

	/* ACK the interrupt. */
	b43_write32(dev, B43_MMIO_GEN_IRQ_REASON, reason);
	b43_write32(dev, B43_MMIO_DMA0_REASON, dev->dma_reason[0]);
	b43_write32(dev, B43_MMIO_DMA1_REASON, dev->dma_reason[1]);
	b43_write32(dev, B43_MMIO_DMA2_REASON, dev->dma_reason[2]);
	b43_write32(dev, B43_MMIO_DMA3_REASON, dev->dma_reason[3]);
	b43_write32(dev, B43_MMIO_DMA4_REASON, dev->dma_reason[4]);
/* Unused ring
	b43_write32(dev, B43_MMIO_DMA5_REASON, dev->dma_reason[5]);
*/

	/* Disable IRQs on the device. The IRQ thread handler will re-enable them. */
	b43_write32(dev, B43_MMIO_GEN_IRQ_MASK, 0);
	/* Save the reason bitmasks for the IRQ thread handler. */
	dev->irq_reason = reason;

	return IRQ_WAKE_THREAD;
}