#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; void* name; } ;
struct tm2_touchkey_data {TYPE_5__ led_dev; TYPE_2__* input_dev; TYPE_4__* regulators; int /*<<< orphan*/  vdd; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct TYPE_10__ {char* supply; int /*<<< orphan*/  consumer; } ;
struct TYPE_8__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_9__ {TYPE_1__ id; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_BACK ; 
 int /*<<< orphan*/  KEY_PHONE ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_ON ; 
 void* TM2_TOUCHKEY_DEV_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tm2_touchkey_data*) ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct tm2_touchkey_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct tm2_touchkey_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tm2_touchkey_data*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm2_touchkey_irq_handler ; 
 int /*<<< orphan*/  tm2_touchkey_led_brightness_set ; 
 int /*<<< orphan*/  tm2_touchkey_power_disable ; 
 int tm2_touchkey_power_enable (struct tm2_touchkey_data*) ; 

__attribute__((used)) static int tm2_touchkey_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct tm2_touchkey_data *touchkey;
	int error;

	if (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "incompatible I2C adapter\n");
		return -EIO;
	}

	touchkey = devm_kzalloc(&client->dev, sizeof(*touchkey), GFP_KERNEL);
	if (!touchkey)
		return -ENOMEM;

	touchkey->client = client;
	i2c_set_clientdata(client, touchkey);

	touchkey->regulators[0].supply = "vcc";
	touchkey->regulators[1].supply = "vdd";
	error = devm_regulator_bulk_get(&client->dev,
					ARRAY_SIZE(touchkey->regulators),
					touchkey->regulators);
	if (error) {
		dev_err(&client->dev, "failed to get regulators: %d\n", error);
		return error;
	}

	/* Save VDD for easy access */
	touchkey->vdd = touchkey->regulators[1].consumer;

	error = tm2_touchkey_power_enable(touchkey);
	if (error) {
		dev_err(&client->dev, "failed to power up device: %d\n", error);
		return error;
	}

	error = devm_add_action_or_reset(&client->dev,
					 tm2_touchkey_power_disable, touchkey);
	if (error) {
		dev_err(&client->dev,
			"failed to install poweroff handler: %d\n", error);
		return error;
	}

	/* input device */
	touchkey->input_dev = devm_input_allocate_device(&client->dev);
	if (!touchkey->input_dev) {
		dev_err(&client->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	touchkey->input_dev->name = TM2_TOUCHKEY_DEV_NAME;
	touchkey->input_dev->id.bustype = BUS_I2C;

	input_set_capability(touchkey->input_dev, EV_KEY, KEY_PHONE);
	input_set_capability(touchkey->input_dev, EV_KEY, KEY_BACK);

	error = input_register_device(touchkey->input_dev);
	if (error) {
		dev_err(&client->dev,
			"failed to register input device: %d\n", error);
		return error;
	}

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, tm2_touchkey_irq_handler,
					  IRQF_ONESHOT,
					  TM2_TOUCHKEY_DEV_NAME, touchkey);
	if (error) {
		dev_err(&client->dev,
			"failed to request threaded irq: %d\n", error);
		return error;
	}

	/* led device */
	touchkey->led_dev.name = TM2_TOUCHKEY_DEV_NAME;
	touchkey->led_dev.brightness = LED_FULL;
	touchkey->led_dev.max_brightness = LED_ON;
	touchkey->led_dev.brightness_set = tm2_touchkey_led_brightness_set;

	error = devm_led_classdev_register(&client->dev, &touchkey->led_dev);
	if (error) {
		dev_err(&client->dev,
			"failed to register touchkey led: %d\n", error);
		return error;
	}

	return 0;
}