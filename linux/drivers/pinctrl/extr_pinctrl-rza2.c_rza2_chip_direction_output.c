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
struct rza2_pinctrl_priv {int /*<<< orphan*/  base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct rza2_pinctrl_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  rza2_chip_set (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  rza2_pin_to_gpio (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rza2_chip_direction_output(struct gpio_chip *chip,
				      unsigned int offset, int val)
{
	struct rza2_pinctrl_priv *priv = gpiochip_get_data(chip);

	rza2_chip_set(chip, offset, val);
	rza2_pin_to_gpio(priv->base, offset, 0);

	return 0;
}