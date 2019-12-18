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
struct xlp_gpio_priv {int /*<<< orphan*/  gpio_paddrv; } ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct xlp_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  xlp_gpio_set_reg (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void xlp_gpio_set(struct gpio_chip *gc, unsigned gpio, int state)
{
	struct xlp_gpio_priv *priv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xlp_gpio_set_reg(priv->gpio_paddrv, gpio, state);
}