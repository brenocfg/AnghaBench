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
typedef  int /*<<< orphan*/  u32 ;
struct meson_gpio_irq_controller {int dummy; } ;
struct irq_domain {struct meson_gpio_irq_controller* host_data; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/ * irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  meson_gpio_irq_release_channel (struct meson_gpio_irq_controller*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void meson_gpio_irq_domain_free(struct irq_domain *domain,
				       unsigned int virq,
				       unsigned int nr_irqs)
{
	struct meson_gpio_irq_controller *ctl = domain->host_data;
	struct irq_data *irq_data;
	u32 *channel_hwirq;

	if (WARN_ON(nr_irqs != 1))
		return;

	irq_domain_free_irqs_parent(domain, virq, 1);

	irq_data = irq_domain_get_irq_data(domain, virq);
	channel_hwirq = irq_data_get_irq_chip_data(irq_data);

	meson_gpio_irq_release_channel(ctl, channel_hwirq);
}