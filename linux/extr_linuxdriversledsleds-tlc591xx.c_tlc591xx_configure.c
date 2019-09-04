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
struct tlc591xx_priv {struct tlc591xx_led* leds; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness_set_blocking; } ;
struct tlc591xx_led {unsigned int led_no; TYPE_1__ ldev; struct tlc591xx_priv* priv; int /*<<< orphan*/  active; } ;
struct tlc591xx {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  MODE2_DIM ; 
 unsigned int TLC591XX_MAX_LEDS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  tlc591xx_brightness_set ; 
 int /*<<< orphan*/  tlc591xx_destroy_devices (struct tlc591xx_priv*,unsigned int) ; 
 int /*<<< orphan*/  tlc591xx_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tlc591xx_configure(struct device *dev,
		   struct tlc591xx_priv *priv,
		   const struct tlc591xx *tlc591xx)
{
	unsigned int i;
	int err = 0;

	tlc591xx_set_mode(priv->regmap, MODE2_DIM);
	for (i = 0; i < TLC591XX_MAX_LEDS; i++) {
		struct tlc591xx_led *led = &priv->leds[i];

		if (!led->active)
			continue;

		led->priv = priv;
		led->led_no = i;
		led->ldev.brightness_set_blocking = tlc591xx_brightness_set;
		led->ldev.max_brightness = LED_FULL;
		err = led_classdev_register(dev, &led->ldev);
		if (err < 0) {
			dev_err(dev, "couldn't register LED %s\n",
				led->ldev.name);
			goto exit;
		}
	}

	return 0;

exit:
	tlc591xx_destroy_devices(priv, i);
	return err;
}