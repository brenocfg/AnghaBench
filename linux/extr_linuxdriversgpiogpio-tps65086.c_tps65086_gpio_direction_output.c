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
struct tps65086_gpio {TYPE_1__* tps; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  TPS65086_GPOCTRL ; 
 struct tps65086_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65086_gpio_direction_output(struct gpio_chip *chip,
					  unsigned offset, int value)
{
	struct tps65086_gpio *gpio = gpiochip_get_data(chip);

	/* Set the initial value */
	regmap_update_bits(gpio->tps->regmap, TPS65086_GPOCTRL,
			   BIT(4 + offset), value ? BIT(4 + offset) : 0);

	return 0;
}