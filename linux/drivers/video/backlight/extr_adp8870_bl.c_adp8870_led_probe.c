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
struct led_info {int flags; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {void* brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct adp8870_led {int id; int flags; int /*<<< orphan*/  work; TYPE_1__ cdev; void* new_brightness; struct i2c_client* client; } ;
struct adp8870_bl {struct adp8870_led* led; } ;
struct adp8870_backlight_platform_data {int num_leds; int led_fade_law; int led_on_time; int bl_led_assign; struct led_info* leds; int /*<<< orphan*/  led_fade_out; int /*<<< orphan*/  led_fade_in; } ;

/* Variables and functions */
 int ADP8870_FLAG_LED_MASK ; 
 int /*<<< orphan*/  ADP8870_ISCF ; 
 int /*<<< orphan*/  ADP8870_ISCLAW ; 
 int /*<<< orphan*/  ADP8870_ISCT1 ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FADE_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FLAG_OFFT_SHIFT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* LED_OFF ; 
 int /*<<< orphan*/  adp8870_led_set ; 
 int adp8870_led_setup (struct adp8870_led*) ; 
 int /*<<< orphan*/  adp8870_led_work ; 
 int adp8870_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct adp8870_backlight_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct adp8870_led* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct adp8870_bl* i2c_get_clientdata (struct i2c_client*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static int adp8870_led_probe(struct i2c_client *client)
{
	struct adp8870_backlight_platform_data *pdata =
		dev_get_platdata(&client->dev);
	struct adp8870_bl *data = i2c_get_clientdata(client);
	struct adp8870_led *led, *led_dat;
	struct led_info *cur_led;
	int ret, i;

	led = devm_kcalloc(&client->dev, pdata->num_leds, sizeof(*led),
				GFP_KERNEL);
	if (led == NULL)
		return -ENOMEM;

	ret = adp8870_write(client, ADP8870_ISCLAW, pdata->led_fade_law);
	if (ret)
		return ret;

	ret = adp8870_write(client, ADP8870_ISCT1,
			(pdata->led_on_time & 0x3) << 6);
	if (ret)
		return ret;

	ret = adp8870_write(client, ADP8870_ISCF,
			FADE_VAL(pdata->led_fade_in, pdata->led_fade_out));
	if (ret)
		return ret;

	for (i = 0; i < pdata->num_leds; ++i) {
		cur_led = &pdata->leds[i];
		led_dat = &led[i];

		led_dat->id = cur_led->flags & ADP8870_FLAG_LED_MASK;

		if (led_dat->id > 7 || led_dat->id < 1) {
			dev_err(&client->dev, "Invalid LED ID %d\n",
				led_dat->id);
			ret = -EINVAL;
			goto err;
		}

		if (pdata->bl_led_assign & (1 << (led_dat->id - 1))) {
			dev_err(&client->dev, "LED %d used by Backlight\n",
				led_dat->id);
			ret = -EBUSY;
			goto err;
		}

		led_dat->cdev.name = cur_led->name;
		led_dat->cdev.default_trigger = cur_led->default_trigger;
		led_dat->cdev.brightness_set = adp8870_led_set;
		led_dat->cdev.brightness = LED_OFF;
		led_dat->flags = cur_led->flags >> FLAG_OFFT_SHIFT;
		led_dat->client = client;
		led_dat->new_brightness = LED_OFF;
		INIT_WORK(&led_dat->work, adp8870_led_work);

		ret = led_classdev_register(&client->dev, &led_dat->cdev);
		if (ret) {
			dev_err(&client->dev, "failed to register LED %d\n",
				led_dat->id);
			goto err;
		}

		ret = adp8870_led_setup(led_dat);
		if (ret) {
			dev_err(&client->dev, "failed to write\n");
			i++;
			goto err;
		}
	}

	data->led = led;

	return 0;

 err:
	for (i = i - 1; i >= 0; --i) {
		led_classdev_unregister(&led[i].cdev);
		cancel_work_sync(&led[i].work);
	}

	return ret;
}