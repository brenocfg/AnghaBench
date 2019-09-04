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
 int /*<<< orphan*/  TPS6586X_GPIOSET1 ; 
 struct tps6586x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  tps6586x_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int tps6586x_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tps6586x_gpio_output(struct gpio_chip *gc, unsigned offset,
				int value)
{
	struct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);
	uint8_t val, mask;

	tps6586x_gpio_set(gc, offset, value);

	val = 0x1 << (offset * 2);
	mask = 0x3 << (offset * 2);

	return tps6586x_update(tps6586x_gpio->parent, TPS6586X_GPIOSET1,
				val, mask);
}