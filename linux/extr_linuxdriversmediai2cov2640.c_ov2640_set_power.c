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
struct ov2640_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ov2640_set_power(struct ov2640_priv *priv, int on)
{
#ifdef CONFIG_GPIOLIB
	if (priv->pwdn_gpio)
		gpiod_direction_output(priv->pwdn_gpio, !on);
	if (on && priv->resetb_gpio) {
		/* Active the resetb pin to perform a reset pulse */
		gpiod_direction_output(priv->resetb_gpio, 1);
		usleep_range(3000, 5000);
		gpiod_set_value(priv->resetb_gpio, 0);
	}
#endif
}