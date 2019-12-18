#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  (* brightness_set_blocking ) (TYPE_2__*,void*) ;void* max_brightness; void* brightness; void* name; } ;
struct tm2_touchkey_data {int num_keycodes; TYPE_2__ led_dev; TYPE_4__* variant; TYPE_6__* input_dev; TYPE_3__* keycodes; TYPE_3__* regulators; int /*<<< orphan*/  vdd; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_26__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_5__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_27__ {TYPE_1__ id; void* name; } ;
struct TYPE_25__ {scalar_t__ fixed_regulator; } ;
struct TYPE_24__ {char* supply; int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 TYPE_3__ KEY_BACK ; 
 TYPE_3__ KEY_PHONE ; 
 void* LED_ON ; 
 void* TM2_TOUCHKEY_DEV_NAME ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int devm_add_action_or_reset (TYPE_5__*,int /*<<< orphan*/ ,struct tm2_touchkey_data*) ; 
 TYPE_6__* devm_input_allocate_device (TYPE_5__*) ; 
 struct tm2_touchkey_data* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (TYPE_5__*,TYPE_2__*) ; 
 int devm_regulator_bulk_get (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int devm_request_threaded_irq (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct tm2_touchkey_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tm2_touchkey_data*) ; 
 int input_register_device (TYPE_6__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_6__*,int /*<<< orphan*/ ,TYPE_3__) ; 
 TYPE_4__* of_device_get_match_data (TYPE_5__*) ; 
 int of_property_read_variable_u32_array (struct device_node*,char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm2_touchkey_irq_handler ; 
 int /*<<< orphan*/  tm2_touchkey_led_brightness_set (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  tm2_touchkey_power_disable ; 
 int tm2_touchkey_power_enable (struct tm2_touchkey_data*) ; 

__attribute__((used)) static int tm2_touchkey_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct device_node *np = client->dev.of_node;
	struct tm2_touchkey_data *touchkey;
	int error;
	int i;

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

	touchkey->variant = of_device_get_match_data(&client->dev);

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

	touchkey->num_keycodes = of_property_read_variable_u32_array(np,
					"linux,keycodes", touchkey->keycodes, 0,
					ARRAY_SIZE(touchkey->keycodes));
	if (touchkey->num_keycodes <= 0) {
		/* default keycodes */
		touchkey->keycodes[0] = KEY_PHONE;
		touchkey->keycodes[1] = KEY_BACK;
		touchkey->num_keycodes = 2;
	}

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

	for (i = 0; i < touchkey->num_keycodes; i++)
		input_set_capability(touchkey->input_dev, EV_KEY,
				     touchkey->keycodes[i]);

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
	touchkey->led_dev.brightness = LED_ON;
	touchkey->led_dev.max_brightness = LED_ON;
	touchkey->led_dev.brightness_set_blocking =
					tm2_touchkey_led_brightness_set;

	error = devm_led_classdev_register(&client->dev, &touchkey->led_dev);
	if (error) {
		dev_err(&client->dev,
			"failed to register touchkey led: %d\n", error);
		return error;
	}

	if (touchkey->variant->fixed_regulator)
		tm2_touchkey_led_brightness_set(&touchkey->led_dev, LED_ON);

	return 0;
}