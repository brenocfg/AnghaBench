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
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int pinctrl_gpio_request (unsigned int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_rcar_request(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_rcar_priv *p = gpiochip_get_data(chip);
	int error;

	error = pm_runtime_get_sync(p->dev);
	if (error < 0)
		return error;

	error = pinctrl_gpio_request(chip->base + offset);
	if (error)
		pm_runtime_put(p->dev);

	return error;
}