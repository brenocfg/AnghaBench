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
struct gpio_chip {int dummy; } ;
struct as3722_pctrl_info {int /*<<< orphan*/  as3722; } ;

/* Variables and functions */
 int as3722_irq_get_virq (int /*<<< orphan*/ ,unsigned int) ; 
 struct as3722_pctrl_info* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int as3722_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct as3722_pctrl_info *as_pci = gpiochip_get_data(chip);

	return as3722_irq_get_virq(as_pci->as3722, offset);
}