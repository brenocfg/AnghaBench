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
struct cqspi_st {int /*<<< orphan*/  transfer_complete; scalar_t__ iobase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int CQSPI_IRQ_MASK_RD ; 
 unsigned int CQSPI_IRQ_MASK_WR ; 
 scalar_t__ CQSPI_REG_IRQSTATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t cqspi_irq_handler(int this_irq, void *dev)
{
	struct cqspi_st *cqspi = dev;
	unsigned int irq_status;

	/* Read interrupt status */
	irq_status = readl(cqspi->iobase + CQSPI_REG_IRQSTATUS);

	/* Clear interrupt */
	writel(irq_status, cqspi->iobase + CQSPI_REG_IRQSTATUS);

	irq_status &= CQSPI_IRQ_MASK_RD | CQSPI_IRQ_MASK_WR;

	if (irq_status)
		complete(&cqspi->transfer_complete);

	return IRQ_HANDLED;
}