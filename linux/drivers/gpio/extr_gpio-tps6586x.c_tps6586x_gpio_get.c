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
typedef  int uint8_t ;
struct tps6586x_gpio {int /*<<< orphan*/  parent; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS6586X_GPIOSET2 ; 
 struct tps6586x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int tps6586x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tps6586x_gpio_get(struct gpio_chip *gc, unsigned offset)
{
	struct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);
	uint8_t val;
	int ret;

	ret = tps6586x_read(tps6586x_gpio->parent, TPS6586X_GPIOSET2, &val);
	if (ret)
		return ret;

	return !!(val & (1 << offset));
}