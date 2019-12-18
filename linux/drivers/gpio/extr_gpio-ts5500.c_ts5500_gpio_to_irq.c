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
struct ts5500_priv {int hwirq; scalar_t__ strap; struct ts5500_dio* pinout; } ;
struct ts5500_dio {int irq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct ts5500_priv* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int ts5500_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct ts5500_priv *priv = gpiochip_get_data(chip);
	const struct ts5500_dio *block = priv->pinout;
	const struct ts5500_dio line = block[offset];

	/* Only one pin is connected to an interrupt */
	if (line.irq)
		return line.irq;

	/* As this pin is input-only, we may strap it to another in/out pin */
	if (priv->strap)
		return priv->hwirq;

	return -ENXIO;
}