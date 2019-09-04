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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct bcm_kona_gpio {TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gpiochip_lock_as_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct bcm_kona_gpio* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int bcm_kona_gpio_irq_reqres(struct irq_data *d)
{
	struct bcm_kona_gpio *kona_gpio = irq_data_get_irq_chip_data(d);
	int ret;

	ret = gpiochip_lock_as_irq(&kona_gpio->gpio_chip, d->hwirq);
	if (ret) {
		dev_err(kona_gpio->gpio_chip.parent,
			"unable to lock HW IRQ %lu for IRQ\n",
			d->hwirq);
		return ret;
	}
	return 0;
}