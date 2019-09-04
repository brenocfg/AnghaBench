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
struct mmio_74xx_gpio_priv {int flags; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int MMIO_74XX_DIR_OUT ; 
 struct mmio_74xx_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int mmio_74xx_get_direction(struct gpio_chip *gc, unsigned offset)
{
	struct mmio_74xx_gpio_priv *priv = gpiochip_get_data(gc);

	return !(priv->flags & MMIO_74XX_DIR_OUT);
}