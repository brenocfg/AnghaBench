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
struct lp873x_gpio {TYPE_1__* lp873; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int BITS_PER_GPO ; 
 int /*<<< orphan*/  LP873X_REG_GPO_CTRL ; 
 struct lp873x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp873x_gpio_direction_output(struct gpio_chip *chip,
					unsigned int offset, int value)
{
	struct lp873x_gpio *gpio = gpiochip_get_data(chip);

	/* Set the initial value */
	return regmap_update_bits(gpio->lp873->regmap, LP873X_REG_GPO_CTRL,
				  BIT(offset * BITS_PER_GPO),
				  value ? BIT(offset * BITS_PER_GPO) : 0);
}