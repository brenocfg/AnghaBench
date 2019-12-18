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
struct msm_pinctrl {int /*<<< orphan*/  pctrl; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int /*<<< orphan*/  owner; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct msm_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ gpiochip_lock_as_irq (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gpio_direction_input (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 int msm_pinmux_request_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_gpio_irq_reqres(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct msm_pinctrl *pctrl = gpiochip_get_data(gc);
	int ret;

	if (!try_module_get(gc->owner))
		return -ENODEV;

	ret = msm_pinmux_request_gpio(pctrl->pctrl, NULL, d->hwirq);
	if (ret)
		goto out;
	msm_gpio_direction_input(gc, d->hwirq);

	if (gpiochip_lock_as_irq(gc, d->hwirq)) {
		dev_err(gc->parent,
			"unable to lock HW IRQ %lu for IRQ\n",
			d->hwirq);
		ret = -EINVAL;
		goto out;
	}
	return 0;
out:
	module_put(gc->owner);
	return ret;
}