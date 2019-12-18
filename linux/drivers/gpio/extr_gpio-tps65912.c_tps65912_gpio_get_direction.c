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
 int GPIO_CFG_MASK ; 
 unsigned int TPS65912_GPIO1 ; 
 struct tps65912_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static int tps65912_gpio_get_direction(struct gpio_chip *gc,
				       unsigned offset)
{
	struct tps65912_gpio *gpio = gpiochip_get_data(gc);

	int ret, val;

	ret = regmap_read(gpio->tps->regmap, TPS65912_GPIO1 + offset, &val);
	if (ret)
		return ret;

	if (val & GPIO_CFG_MASK)
		return 0;
	else
		return 1;
}