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
struct puv3_irq_state {int iccr; int iclr; int icmr; scalar_t__ saved; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GFER ; 
 int /*<<< orphan*/  GPIO_GRER ; 
 int GPIO_IRQ_falling_edge ; 
 int GPIO_IRQ_mask ; 
 int GPIO_IRQ_rising_edge ; 
 int /*<<< orphan*/  INTC_ICCR ; 
 int /*<<< orphan*/  INTC_ICLR ; 
 int /*<<< orphan*/  INTC_ICMR ; 
 struct puv3_irq_state puv3_irq_state ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void puv3_irq_resume(void)
{
	struct puv3_irq_state *st = &puv3_irq_state;

	if (st->saved) {
		writel(st->iccr, INTC_ICCR);
		writel(st->iclr, INTC_ICLR);

		writel(GPIO_IRQ_rising_edge & GPIO_IRQ_mask, GPIO_GRER);
		writel(GPIO_IRQ_falling_edge & GPIO_IRQ_mask, GPIO_GFER);

		writel(st->icmr, INTC_ICMR);
	}
}