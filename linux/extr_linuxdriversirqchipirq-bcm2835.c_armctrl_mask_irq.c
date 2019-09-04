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
struct irq_data {scalar_t__ hwirq; } ;
struct TYPE_2__ {scalar_t__* disable; scalar_t__ base; } ;

/* Variables and functions */
 size_t HWIRQ_BANK (scalar_t__) ; 
 int /*<<< orphan*/  HWIRQ_BIT (scalar_t__) ; 
 scalar_t__ NUMBER_IRQS ; 
 scalar_t__ REG_FIQ_CONTROL ; 
 int /*<<< orphan*/  REG_FIQ_DISABLE ; 
 TYPE_1__ intc ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void armctrl_mask_irq(struct irq_data *d)
{
	if (d->hwirq >= NUMBER_IRQS)
		writel_relaxed(REG_FIQ_DISABLE, intc.base + REG_FIQ_CONTROL);
	else
		writel_relaxed(HWIRQ_BIT(d->hwirq),
			       intc.disable[HWIRQ_BANK(d->hwirq)]);
}