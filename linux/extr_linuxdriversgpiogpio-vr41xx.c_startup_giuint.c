#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gpiochip_lock_as_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  unmask_giuint_low (struct irq_data*) ; 
 TYPE_1__ vr41xx_gpio_chip ; 

__attribute__((used)) static unsigned int startup_giuint(struct irq_data *data)
{
	int ret;

	ret = gpiochip_lock_as_irq(&vr41xx_gpio_chip, irqd_to_hwirq(data));
	if (ret) {
		dev_err(vr41xx_gpio_chip.parent,
			"unable to lock HW IRQ %lu for IRQ\n",
			data->hwirq);
		return ret;
	}

	/* Satisfy the .enable semantics by unmasking the line */
	unmask_giuint_low(data);
	return 0;
}