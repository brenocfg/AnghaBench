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
struct tps6586x_gpio {int /*<<< orphan*/  parent; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS6586X_GPIOSET2 ; 
 struct tps6586x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  tps6586x_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void tps6586x_gpio_set(struct gpio_chip *gc, unsigned offset,
			      int value)
{
	struct tps6586x_gpio *tps6586x_gpio = gpiochip_get_data(gc);

	tps6586x_update(tps6586x_gpio->parent, TPS6586X_GPIOSET2,
			value << offset, 1 << offset);
}