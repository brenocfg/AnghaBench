#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int dummy; } ;
typedef  size_t irq_hw_number_t ;
struct TYPE_4__ {scalar_t__ base; } ;
struct TYPE_3__ {scalar_t__ eoi; } ;

/* Variables and functions */
 TYPE_2__* clps711x_intc ; 
 TYPE_1__* clps711x_irqs ; 
 size_t irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clps711x_intc_eoi(struct irq_data *d)
{
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	writel_relaxed(0, clps711x_intc->base + clps711x_irqs[hwirq].eoi);
}