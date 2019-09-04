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

/* Variables and functions */
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  IT8152_INTC_LDCNIMR ; 
 int /*<<< orphan*/  IT8152_INTC_LDCNIRR ; 
 int /*<<< orphan*/  IT8152_INTC_LPCNIMR ; 
 int /*<<< orphan*/  IT8152_INTC_LPCNIRR ; 
 int /*<<< orphan*/  IT8152_INTC_PDCNIMR ; 
 int /*<<< orphan*/  IT8152_INTC_PDCNIRR ; 
 int IT8152_IRQ (int /*<<< orphan*/ ) ; 
 int IT8152_LAST_IRQ ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it8152_irq_chip ; 

void it8152_init_irq(void)
{
	int irq;

	__raw_writel((0xffff), IT8152_INTC_PDCNIMR);
	__raw_writel((0), IT8152_INTC_PDCNIRR);
	__raw_writel((0xffff), IT8152_INTC_LPCNIMR);
	__raw_writel((0), IT8152_INTC_LPCNIRR);
	__raw_writel((0xffff), IT8152_INTC_LDCNIMR);
	__raw_writel((0), IT8152_INTC_LDCNIRR);

	for (irq = IT8152_IRQ(0); irq <= IT8152_LAST_IRQ; irq++) {
		irq_set_chip_and_handler(irq, &it8152_irq_chip,
					 handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	}
}