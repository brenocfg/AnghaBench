#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ irq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN4I_IRQ_PENDING_REG (int /*<<< orphan*/ ) ; 
 TYPE_1__* irq_ic_data ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_irq_ack(struct irq_data *irqd)
{
	unsigned int irq = irqd_to_hwirq(irqd);

	if (irq != 0)
		return; /* Only IRQ 0 / the ENMI needs to be acked */

	writel(BIT(0), irq_ic_data->irq_base + SUN4I_IRQ_PENDING_REG(0));
}