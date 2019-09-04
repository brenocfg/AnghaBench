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
struct tps65912_gpio {TYPE_1__* tps; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_SET_MASK ; 
 unsigned int TPS65912_GPIO1 ; 
 struct tps65912_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tps65912_gpio_set(struct gpio_chip *gc, unsigned offset,
			      int value)
{
	struct tps65912_gpio *gpio = gpiochip_get_data(gc);

	regmap_update_bits(gpio->tps->regmap, TPS65912_GPIO1 + offset,
			   GPIO_SET_MASK, value ? GPIO_SET_MASK : 0);
}