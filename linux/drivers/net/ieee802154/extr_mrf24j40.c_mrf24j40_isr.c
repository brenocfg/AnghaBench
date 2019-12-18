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
struct mrf24j40 {int /*<<< orphan*/  irq_msg; int /*<<< orphan*/  spi; scalar_t__* irq_buf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MRF24J40_READSHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_INTSTAT ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int spi_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mrf24j40_isr(int irq, void *data)
{
	struct mrf24j40 *devrec = data;
	int ret;

	disable_irq_nosync(irq);

	devrec->irq_buf[0] = MRF24J40_READSHORT(REG_INTSTAT);
	devrec->irq_buf[1] = 0;

	/* Read the interrupt status */
	ret = spi_async(devrec->spi, &devrec->irq_msg);
	if (ret) {
		enable_irq(irq);
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}