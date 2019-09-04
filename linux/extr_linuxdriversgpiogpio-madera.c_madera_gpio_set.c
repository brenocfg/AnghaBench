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
struct madera_gpio {struct madera* madera; } ;
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int MADERA_GP1_LVL ; 
 int /*<<< orphan*/  MADERA_GP1_LVL_MASK ; 
 scalar_t__ MADERA_GPIO1_CTRL_1 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 struct madera_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void madera_gpio_set(struct gpio_chip *chip, unsigned int offset,
			    int value)
{
	struct madera_gpio *madera_gpio = gpiochip_get_data(chip);
	struct madera *madera = madera_gpio->madera;
	unsigned int reg_offset = 2 * offset;
	unsigned int reg_val = value ? MADERA_GP1_LVL : 0;
	int ret;

	ret = regmap_update_bits(madera->regmap,
				 MADERA_GPIO1_CTRL_1 + reg_offset,
				 MADERA_GP1_LVL_MASK, reg_val);

	/* set() doesn't return an error so log a warning */
	if (ret)
		dev_warn(madera->dev, "Failed to write to 0x%x (%d)\n",
			 MADERA_GPIO1_CTRL_1 + reg_offset, ret);
}