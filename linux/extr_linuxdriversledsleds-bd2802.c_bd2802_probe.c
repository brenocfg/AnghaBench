#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct bd2802_led_platform_data {int /*<<< orphan*/  reset_gpio; } ;
struct bd2802_led {struct i2c_client* client; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  rgb_current; int /*<<< orphan*/  wave_pattern; struct bd2802_led_platform_data* pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__**) ; 
 int /*<<< orphan*/  BD2802_CURRENT_032 ; 
 int /*<<< orphan*/  BD2802_PATTERN_HALF ; 
 int /*<<< orphan*/  BD2802_REG_CLKSETUP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 TYPE_2__** bd2802_attributes ; 
 int bd2802_register_led_classdev (struct bd2802_led*) ; 
 int bd2802_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct bd2802_led_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int device_create_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct bd2802_led* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bd2802_led*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bd2802_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct bd2802_led *led;
	struct bd2802_led_platform_data *pdata;
	int ret, i;

	led = devm_kzalloc(&client->dev, sizeof(struct bd2802_led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->client = client;
	pdata = led->pdata = dev_get_platdata(&client->dev);
	i2c_set_clientdata(client, led);

	/* Configure RESET GPIO (L: RESET, H: RESET cancel) */
	gpio_request_one(pdata->reset_gpio, GPIOF_OUT_INIT_HIGH, "RGB_RESETB");

	/* Tacss = min 0.1ms */
	udelay(100);

	/* Detect BD2802GU */
	ret = bd2802_write_byte(client, BD2802_REG_CLKSETUP, 0x00);
	if (ret < 0) {
		dev_err(&client->dev, "failed to detect device\n");
		return ret;
	} else
		dev_info(&client->dev, "return 0x%02x\n", ret);

	/* To save the power, reset BD2802 after detecting */
	gpio_set_value(led->pdata->reset_gpio, 0);

	/* Default attributes */
	led->wave_pattern = BD2802_PATTERN_HALF;
	led->rgb_current = BD2802_CURRENT_032;

	init_rwsem(&led->rwsem);

	for (i = 0; i < ARRAY_SIZE(bd2802_attributes); i++) {
		ret = device_create_file(&led->client->dev,
						bd2802_attributes[i]);
		if (ret) {
			dev_err(&led->client->dev, "failed: sysfs file %s\n",
					bd2802_attributes[i]->attr.name);
			goto failed_unregister_dev_file;
		}
	}

	ret = bd2802_register_led_classdev(led);
	if (ret < 0)
		goto failed_unregister_dev_file;

	return 0;

failed_unregister_dev_file:
	for (i--; i >= 0; i--)
		device_remove_file(&led->client->dev, bd2802_attributes[i]);
	return ret;
}