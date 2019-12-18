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
struct mcr20a_local {int /*<<< orphan*/  irq_msg; int /*<<< orphan*/  spi; int /*<<< orphan*/ * irq_header; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAR_IRQ_STS1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MCR20A_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int spi_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mcr20a_irq_isr(int irq, void *data)
{
	struct mcr20a_local *lp = data;
	int ret;

	disable_irq_nosync(irq);

	lp->irq_header[0] = MCR20A_READ_REG(DAR_IRQ_STS1);
	/* read IRQSTSx */
	ret = spi_async(lp->spi, &lp->irq_msg);
	if (ret) {
		enable_irq(irq);
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}