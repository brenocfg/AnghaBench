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
typedef  int uint32_t ;
struct bcm_kona_i2c_dev {int /*<<< orphan*/  done; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISR_NOACK_MASK ; 
 scalar_t__ ISR_OFFSET ; 
 int ISR_RESERVED_MASK ; 
 int TXFCR_FIFO_EN_MASK ; 
 int TXFCR_FIFO_FLUSH_MASK ; 
 scalar_t__ TXFCR_OFFSET ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t bcm_kona_i2c_isr(int irq, void *devid)
{
	struct bcm_kona_i2c_dev *dev = devid;
	uint32_t status = readl(dev->base + ISR_OFFSET);

	if ((status & ~ISR_RESERVED_MASK) == 0)
		return IRQ_NONE;

	/* Must flush the TX FIFO when NAK detected */
	if (status & ISR_NOACK_MASK)
		writel(TXFCR_FIFO_FLUSH_MASK | TXFCR_FIFO_EN_MASK,
		       dev->base + TXFCR_OFFSET);

	writel(status & ~ISR_RESERVED_MASK, dev->base + ISR_OFFSET);
	complete(&dev->done);

	return IRQ_HANDLED;
}