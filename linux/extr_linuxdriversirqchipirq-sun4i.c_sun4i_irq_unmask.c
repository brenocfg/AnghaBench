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
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ SUN4I_IRQ_ENABLE_REG (int) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ sun4i_irq_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sun4i_irq_unmask(struct irq_data *irqd)
{
	unsigned int irq = irqd_to_hwirq(irqd);
	unsigned int irq_off = irq % 32;
	int reg = irq / 32;
	u32 val;

	val = readl(sun4i_irq_base + SUN4I_IRQ_ENABLE_REG(reg));
	writel(val | (1 << irq_off),
	       sun4i_irq_base + SUN4I_IRQ_ENABLE_REG(reg));
}