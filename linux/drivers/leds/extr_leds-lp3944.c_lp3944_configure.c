#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lp3944_platform_data {int leds_size; struct lp3944_led* leds; } ;
struct TYPE_3__ {int max_brightness; int brightness; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set_blocking; } ;
struct lp3944_led_data {int id; int type; TYPE_1__ ldev; struct i2c_client* client; } ;
struct lp3944_led {int type; int /*<<< orphan*/  status; int /*<<< orphan*/  name; } ;
struct lp3944_data {struct lp3944_led_data* leds; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
#define  LP3944_LED_TYPE_LED 130 
#define  LP3944_LED_TYPE_LED_INVERTED 129 
#define  LP3944_LED_TYPE_NONE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int lp3944_led_set (struct lp3944_led_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp3944_led_set_blink ; 
 int /*<<< orphan*/  lp3944_led_set_brightness ; 

__attribute__((used)) static int lp3944_configure(struct i2c_client *client,
			    struct lp3944_data *data,
			    struct lp3944_platform_data *pdata)
{
	int i, err = 0;

	for (i = 0; i < pdata->leds_size; i++) {
		struct lp3944_led *pled = &pdata->leds[i];
		struct lp3944_led_data *led = &data->leds[i];
		led->client = client;
		led->id = i;

		switch (pled->type) {

		case LP3944_LED_TYPE_LED:
		case LP3944_LED_TYPE_LED_INVERTED:
			led->type = pled->type;
			led->ldev.name = pled->name;
			led->ldev.max_brightness = 1;
			led->ldev.brightness_set_blocking =
						lp3944_led_set_brightness;
			led->ldev.blink_set = lp3944_led_set_blink;
			led->ldev.flags = LED_CORE_SUSPENDRESUME;

			err = led_classdev_register(&client->dev, &led->ldev);
			if (err < 0) {
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led->ldev.name);
				goto exit;
			}

			/* to expose the default value to userspace */
			led->ldev.brightness =
					(enum led_brightness) pled->status;

			/* Set the default led status */
			err = lp3944_led_set(led, pled->status);
			if (err < 0) {
				dev_err(&client->dev,
					"%s couldn't set STATUS %d\n",
					led->ldev.name, pled->status);
				goto exit;
			}
			break;

		case LP3944_LED_TYPE_NONE:
		default:
			break;

		}
	}
	return 0;

exit:
	if (i > 0)
		for (i = i - 1; i >= 0; i--)
			switch (pdata->leds[i].type) {

			case LP3944_LED_TYPE_LED:
			case LP3944_LED_TYPE_LED_INVERTED:
				led_classdev_unregister(&data->leds[i].ldev);
				break;

			case LP3944_LED_TYPE_NONE:
			default:
				break;
			}

	return err;
}