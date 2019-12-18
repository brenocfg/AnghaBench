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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct exiu_irq_data {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ EIREQCLR ; 
 int /*<<< orphan*/  irq_chip_eoi_parent (struct irq_data*) ; 
 struct exiu_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void exiu_irq_eoi(struct irq_data *d)
{
	struct exiu_irq_data *data = irq_data_get_irq_chip_data(d);

	writel(BIT(d->hwirq), data->base + EIREQCLR);
	irq_chip_eoi_parent(d);
}