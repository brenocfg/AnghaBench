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
struct tps65218_gpio {struct tps65218* tps65218; } ;
struct tps65218 {int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int TPS65218_ENABLE2_GPIO1 ; 
 int /*<<< orphan*/  TPS65218_REG_ENABLE2 ; 
 struct tps65218_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int tps65218_gpio_get(struct gpio_chip *gc, unsigned offset)
{
	struct tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	struct tps65218 *tps65218 = tps65218_gpio->tps65218;
	unsigned int val;
	int ret;

	ret = regmap_read(tps65218->regmap, TPS65218_REG_ENABLE2, &val);
	if (ret)
		return ret;

	return !!(val & (TPS65218_ENABLE2_GPIO1 << offset));
}