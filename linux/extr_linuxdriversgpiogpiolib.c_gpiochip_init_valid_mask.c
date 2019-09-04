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
struct gpio_chip {int /*<<< orphan*/  valid_mask; int /*<<< orphan*/  need_valid_mask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  gpiochip_allocate_mask (struct gpio_chip*) ; 

__attribute__((used)) static int gpiochip_init_valid_mask(struct gpio_chip *gpiochip)
{
#ifdef CONFIG_OF_GPIO
	int size;
	struct device_node *np = gpiochip->of_node;

	size = of_property_count_u32_elems(np,  "gpio-reserved-ranges");
	if (size > 0 && size % 2 == 0)
		gpiochip->need_valid_mask = true;
#endif

	if (!gpiochip->need_valid_mask)
		return 0;

	gpiochip->valid_mask = gpiochip_allocate_mask(gpiochip);
	if (!gpiochip->valid_mask)
		return -ENOMEM;

	return 0;
}