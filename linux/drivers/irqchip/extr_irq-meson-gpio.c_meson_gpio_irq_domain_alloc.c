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
struct irq_fwspec {int dummy; } ;
struct irq_domain {struct meson_gpio_irq_controller* host_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int meson_gpio_irq_allocate_gic_irq (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  meson_gpio_irq_chip ; 
 int meson_gpio_irq_domain_translate (struct irq_domain*,struct irq_fwspec*,unsigned long*,unsigned int*) ; 
 int /*<<< orphan*/  meson_gpio_irq_release_channel (struct meson_gpio_irq_controller*,int /*<<< orphan*/ *) ; 
 int meson_gpio_irq_request_channel (struct meson_gpio_irq_controller*,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_gpio_irq_domain_alloc(struct irq_domain *domain,
				       unsigned int virq,
				       unsigned int nr_irqs,
				       void *data)
{
	struct irq_fwspec *fwspec = data;
	struct meson_gpio_irq_controller *ctl = domain->host_data;
	unsigned long hwirq;
	u32 *channel_hwirq;
	unsigned int type;
	int ret;

	if (WARN_ON(nr_irqs != 1))
		return -EINVAL;

	ret = meson_gpio_irq_domain_translate(domain, fwspec, &hwirq, &type);
	if (ret)
		return ret;

	ret = meson_gpio_irq_request_channel(ctl, hwirq, &channel_hwirq);
	if (ret)
		return ret;

	ret = meson_gpio_irq_allocate_gic_irq(domain, virq,
					      *channel_hwirq, type);
	if (ret < 0) {
		pr_err("failed to allocate gic irq %u\n", *channel_hwirq);
		meson_gpio_irq_release_channel(ctl, channel_hwirq);
		return ret;
	}

	irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
				      &meson_gpio_irq_chip, channel_hwirq);

	return 0;
}