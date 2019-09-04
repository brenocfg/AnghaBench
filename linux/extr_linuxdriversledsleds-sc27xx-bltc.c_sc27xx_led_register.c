#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sc27xx_led_priv {struct sc27xx_led* leds; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  name; } ;
struct sc27xx_led {int line; TYPE_1__ ldev; int /*<<< orphan*/  name; struct sc27xx_led_priv* priv; int /*<<< orphan*/  active; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SC27XX_LEDS_MAX ; 
 int devm_led_classdev_register (struct device*,TYPE_1__*) ; 
 int sc27xx_led_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc27xx_led_set ; 

__attribute__((used)) static int sc27xx_led_register(struct device *dev, struct sc27xx_led_priv *priv)
{
	int i, err;

	err = sc27xx_led_init(priv->regmap);
	if (err)
		return err;

	for (i = 0; i < SC27XX_LEDS_MAX; i++) {
		struct sc27xx_led *led = &priv->leds[i];

		if (!led->active)
			continue;

		led->line = i;
		led->priv = priv;
		led->ldev.name = led->name;
		led->ldev.brightness_set_blocking = sc27xx_led_set;

		err = devm_led_classdev_register(dev, &led->ldev);
		if (err)
			return err;
	}

	return 0;
}