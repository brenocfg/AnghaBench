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
struct wcove_gpio {int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_IN ; 
 struct wcove_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int to_reg (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcove_gpio_get(struct gpio_chip *chip, unsigned int gpio)
{
	struct wcove_gpio *wg = gpiochip_get_data(chip);
	unsigned int val;
	int ret, reg = to_reg(gpio, CTRL_IN);

	if (reg < 0)
		return 0;

	ret = regmap_read(wg->regmap, reg, &val);
	if (ret)
		return ret;

	return val & 0x1;
}