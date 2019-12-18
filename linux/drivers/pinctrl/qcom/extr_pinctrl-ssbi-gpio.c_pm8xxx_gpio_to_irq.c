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
struct pm8xxx_pin_data {int irq; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_gpio {int /*<<< orphan*/  fwnode; TYPE_2__ desc; } ;
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 scalar_t__ IRQ_TYPE_EDGE_RISING ; 
 scalar_t__ PM8XXX_GPIO_PHYSICAL_OFFSET ; 
 struct pm8xxx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_fwspec_mapping (struct irq_fwspec*) ; 

__attribute__((used)) static int pm8xxx_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	struct irq_fwspec fwspec;
	int ret;

	fwspec.fwnode = pctrl->fwnode;
	fwspec.param_count = 2;
	fwspec.param[0] = offset + PM8XXX_GPIO_PHYSICAL_OFFSET;
	fwspec.param[1] = IRQ_TYPE_EDGE_RISING;

	ret = irq_create_fwspec_mapping(&fwspec);

	/*
	 * Cache the IRQ since pm8xxx_gpio_get() needs this to get determine the
	 * line level.
	 */
	pin->irq = ret;

	return ret;
}