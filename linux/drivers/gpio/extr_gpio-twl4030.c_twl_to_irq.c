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
struct gpio_twl4030_priv {int irq_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TWL4030_GPIO_MAX ; 
 struct gpio_twl4030_priv* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int twl_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_twl4030_priv *priv = gpiochip_get_data(chip);

	return (priv->irq_base && (offset < TWL4030_GPIO_MAX))
		? (priv->irq_base + offset)
		: -EINVAL;
}