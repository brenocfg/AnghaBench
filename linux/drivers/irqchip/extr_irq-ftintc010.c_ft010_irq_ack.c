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
struct irq_data {int dummy; } ;
struct ft010_irq_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT010_IRQ_CLEAR (int /*<<< orphan*/ ) ; 
 struct ft010_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ft010_irq_ack(struct irq_data *d)
{
	struct ft010_irq_data *f = irq_data_get_irq_chip_data(d);

	writel(BIT(irqd_to_hwirq(d)), FT010_IRQ_CLEAR(f->base));
}