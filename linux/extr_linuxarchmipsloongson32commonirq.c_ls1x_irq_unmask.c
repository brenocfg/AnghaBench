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
struct irq_data {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LS1X_INTC_INTIEN (unsigned int) ; 
 int LS1X_IRQ_BASE ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ls1x_irq_unmask(struct irq_data *d)
{
	unsigned int bit = (d->irq - LS1X_IRQ_BASE) & 0x1f;
	unsigned int n = (d->irq - LS1X_IRQ_BASE) >> 5;

	__raw_writel(__raw_readl(LS1X_INTC_INTIEN(n))
			| (1 << bit), LS1X_INTC_INTIEN(n));
}