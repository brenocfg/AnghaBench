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
struct gpio_desc {int /*<<< orphan*/  flags; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IRQ_IS_ENABLED ; 
 int /*<<< orphan*/  FLAG_IS_OUT ; 
 int /*<<< orphan*/  FLAG_USED_AS_IRQ ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gpiochip_enable_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct gpio_desc *desc = gpiochip_get_desc(chip, offset);

	if (!IS_ERR(desc) &&
	    !WARN_ON(!test_bit(FLAG_USED_AS_IRQ, &desc->flags))) {
		WARN_ON(test_bit(FLAG_IS_OUT, &desc->flags));
		set_bit(FLAG_IRQ_IS_ENABLED, &desc->flags);
	}
}