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
struct gpio_rcar_priv {int /*<<< orphan*/  dev; } ;
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_rcar_config_general_input_output_mode (struct gpio_chip*,unsigned int,int) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinctrl_gpio_free (unsigned int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_rcar_free(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_rcar_priv *p = gpiochip_get_data(chip);

	pinctrl_gpio_free(chip->base + offset);

	/*
	 * Set the GPIO as an input to ensure that the next GPIO request won't
	 * drive the GPIO pin as an output.
	 */
	gpio_rcar_config_general_input_output_mode(chip, offset, false);

	pm_runtime_put(p->dev);
}