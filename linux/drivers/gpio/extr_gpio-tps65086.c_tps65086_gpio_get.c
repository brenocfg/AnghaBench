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
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  TPS65086_GPOCTRL ; 
 struct tps65086_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tps65086_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct tps65086_gpio *gpio = gpiochip_get_data(chip);
	int ret, val;

	ret = regmap_read(gpio->tps->regmap, TPS65086_GPOCTRL, &val);
	if (ret < 0)
		return ret;

	return val & BIT(4 + offset);
}