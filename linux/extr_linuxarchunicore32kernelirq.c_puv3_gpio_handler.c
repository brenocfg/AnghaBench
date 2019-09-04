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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GEDR ; 
 unsigned int IRQ_GPIO0 ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void puv3_gpio_handler(struct irq_desc *desc)
{
	unsigned int mask, irq;

	mask = readl(GPIO_GEDR);
	do {
		/*
		 * clear down all currently active IRQ sources.
		 * We will be processing them all.
		 */
		writel(mask, GPIO_GEDR);

		irq = IRQ_GPIO0;
		do {
			if (mask & 1)
				generic_handle_irq(irq);
			mask >>= 1;
			irq++;
		} while (mask);
		mask = readl(GPIO_GEDR);
	} while (mask);
}