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
struct puv3_irq_state {int saved; int icmr; int iclr; int iccr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GEDR ; 
 int /*<<< orphan*/  GPIO_GFER ; 
 int /*<<< orphan*/  GPIO_GRER ; 
 int GPIO_IRQ_falling_edge ; 
 int GPIO_IRQ_rising_edge ; 
 int /*<<< orphan*/  INTC_ICCR ; 
 int /*<<< orphan*/  INTC_ICLR ; 
 int /*<<< orphan*/  INTC_ICMR ; 
 int /*<<< orphan*/  PM_PWER ; 
 struct puv3_irq_state puv3_irq_state ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_irq_suspend(void)
{
	struct puv3_irq_state *st = &puv3_irq_state;

	st->saved = 1;
	st->icmr = readl(INTC_ICMR);
	st->iclr = readl(INTC_ICLR);
	st->iccr = readl(INTC_ICCR);

	/*
	 * Disable all GPIO-based interrupts.
	 */
	writel(readl(INTC_ICMR) & ~(0x1ff), INTC_ICMR);

	/*
	 * Set the appropriate edges for wakeup.
	 */
	writel(readl(PM_PWER) & GPIO_IRQ_rising_edge, GPIO_GRER);
	writel(readl(PM_PWER) & GPIO_IRQ_falling_edge, GPIO_GFER);

	/*
	 * Clear any pending GPIO interrupts.
	 */
	writel(readl(GPIO_GEDR), GPIO_GEDR);

	return 0;
}