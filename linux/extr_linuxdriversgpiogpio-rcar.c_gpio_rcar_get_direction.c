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
struct gpio_rcar_priv {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  INOUTSEL ; 
 int gpio_rcar_read (struct gpio_rcar_priv*,int /*<<< orphan*/ ) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_rcar_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	struct gpio_rcar_priv *p = gpiochip_get_data(chip);

	return !(gpio_rcar_read(p, INOUTSEL) & BIT(offset));
}