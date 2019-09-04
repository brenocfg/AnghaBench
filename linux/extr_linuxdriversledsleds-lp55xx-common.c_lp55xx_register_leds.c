#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct lp55xx_platform_data {int num_channels; TYPE_2__* led_config; } ;
struct lp55xx_led {struct lp55xx_chip* chip; } ;
struct lp55xx_device_config {int /*<<< orphan*/  (* set_led_current ) (struct lp55xx_led*,scalar_t__) ;int /*<<< orphan*/  brightness_fn; } ;
struct lp55xx_chip {int /*<<< orphan*/  num_leds; TYPE_1__* cl; struct lp55xx_device_config* cfg; struct lp55xx_platform_data* pdata; } ;
struct TYPE_4__ {scalar_t__ led_current; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lp55xx_init_led (struct lp55xx_led*,struct lp55xx_chip*,int) ; 
 int /*<<< orphan*/  lp55xx_unregister_leds (struct lp55xx_led*,struct lp55xx_chip*) ; 
 int /*<<< orphan*/  stub1 (struct lp55xx_led*,scalar_t__) ; 

int lp55xx_register_leds(struct lp55xx_led *led, struct lp55xx_chip *chip)
{
	struct lp55xx_platform_data *pdata = chip->pdata;
	struct lp55xx_device_config *cfg = chip->cfg;
	int num_channels = pdata->num_channels;
	struct lp55xx_led *each;
	u8 led_current;
	int ret;
	int i;

	if (!cfg->brightness_fn) {
		dev_err(&chip->cl->dev, "empty brightness configuration\n");
		return -EINVAL;
	}

	for (i = 0; i < num_channels; i++) {

		/* do not initialize channels that are not connected */
		if (pdata->led_config[i].led_current == 0)
			continue;

		led_current = pdata->led_config[i].led_current;
		each = led + i;
		ret = lp55xx_init_led(each, chip, i);
		if (ret)
			goto err_init_led;

		chip->num_leds++;
		each->chip = chip;

		/* setting led current at each channel */
		if (cfg->set_led_current)
			cfg->set_led_current(each, led_current);
	}

	return 0;

err_init_led:
	lp55xx_unregister_leds(led, chip);
	return ret;
}