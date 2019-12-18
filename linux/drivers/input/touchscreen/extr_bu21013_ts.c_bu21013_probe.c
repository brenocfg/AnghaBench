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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {struct input_absinfo* absinfo; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct input_absinfo {scalar_t__ minimum; int /*<<< orphan*/  maximum; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  invert_y; int /*<<< orphan*/  invert_x; } ;
struct bu21013_ts {scalar_t__ int_gpiod; scalar_t__ cs_gpiod; int /*<<< orphan*/  regulator; TYPE_2__ props; struct input_dev* in_dev; void* y_flip; void* x_flip; struct i2c_client* client; } ;

/* Variables and functions */
 size_t ABS_MT_POSITION_X ; 
 size_t ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  DRIVER_TP ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_TRACK ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_FINGERS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (scalar_t__) ; 
 int /*<<< orphan*/  bu21013_disable_chip ; 
 int /*<<< orphan*/  bu21013_gpio_irq ; 
 int bu21013_init_chip (struct bu21013_ts*) ; 
 int /*<<< orphan*/  bu21013_power_off ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bu21013_ts*) ; 
 scalar_t__ devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct bu21013_ts* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bu21013_ts*) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (scalar_t__,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bu21013_ts*) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct bu21013_ts*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,TYPE_2__*) ; 

__attribute__((used)) static int bu21013_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct bu21013_ts *ts;
	struct input_dev *in_dev;
	struct input_absinfo *info;
	u32 max_x = 0, max_y = 0;
	int error;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "i2c smbus byte data not supported\n");
		return -EIO;
	}

	if (!client->irq) {
		dev_err(&client->dev, "No IRQ set up\n");
		return -EINVAL;
	}

	ts = devm_kzalloc(&client->dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	ts->client = client;

	ts->x_flip = device_property_read_bool(&client->dev, "rohm,flip-x");
	ts->y_flip = device_property_read_bool(&client->dev, "rohm,flip-y");

	in_dev = devm_input_allocate_device(&client->dev);
	if (!in_dev) {
		dev_err(&client->dev, "device memory alloc failed\n");
		return -ENOMEM;
	}
	ts->in_dev = in_dev;
	input_set_drvdata(in_dev, ts);

	/* register the device to input subsystem */
	in_dev->name = DRIVER_TP;
	in_dev->id.bustype = BUS_I2C;

	device_property_read_u32(&client->dev, "rohm,touch-max-x", &max_x);
	device_property_read_u32(&client->dev, "rohm,touch-max-y", &max_y);

	input_set_abs_params(in_dev, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_abs_params(in_dev, ABS_MT_POSITION_Y, 0, max_y, 0, 0);

	touchscreen_parse_properties(in_dev, true, &ts->props);

	/* Adjust for the legacy "flip" properties, if present */
	if (!ts->props.invert_x &&
	    device_property_read_bool(&client->dev, "rohm,flip-x")) {
		info = &in_dev->absinfo[ABS_MT_POSITION_X];
		info->maximum -= info->minimum;
		info->minimum = 0;
	}

	if (!ts->props.invert_y &&
	    device_property_read_bool(&client->dev, "rohm,flip-y")) {
		info = &in_dev->absinfo[ABS_MT_POSITION_Y];
		info->maximum -= info->minimum;
		info->minimum = 0;
	}

	error = input_mt_init_slots(in_dev, MAX_FINGERS,
				    INPUT_MT_DIRECT | INPUT_MT_TRACK |
					INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(&client->dev, "failed to initialize MT slots");
		return error;
	}

	ts->regulator = devm_regulator_get(&client->dev, "avdd");
	if (IS_ERR(ts->regulator)) {
		dev_err(&client->dev, "regulator_get failed\n");
		return PTR_ERR(ts->regulator);
	}

	error = regulator_enable(ts->regulator);
	if (error) {
		dev_err(&client->dev, "regulator enable failed\n");
		return error;
	}

	error = devm_add_action_or_reset(&client->dev, bu21013_power_off, ts);
	if (error) {
		dev_err(&client->dev, "failed to install power off handler\n");
		return error;
	}

	/* Named "CS" on the chip, DT binding is "reset" */
	ts->cs_gpiod = devm_gpiod_get(&client->dev, "reset", GPIOD_OUT_HIGH);
	error = PTR_ERR_OR_ZERO(ts->cs_gpiod);
	if (error) {
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev, "failed to get CS GPIO\n");
		return error;
	}
	gpiod_set_consumer_name(ts->cs_gpiod, "BU21013 CS");

	error = devm_add_action_or_reset(&client->dev,
					 bu21013_disable_chip, ts);
	if (error) {
		dev_err(&client->dev,
			"failed to install chip disable handler\n");
		return error;
	}

	/* Named "INT" on the chip, DT binding is "touch" */
	ts->int_gpiod = devm_gpiod_get_optional(&client->dev,
						"touch", GPIOD_IN);
	error = PTR_ERR_OR_ZERO(ts->int_gpiod);
	if (error) {
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev, "failed to get INT GPIO\n");
		return error;
	}

	if (ts->int_gpiod)
		gpiod_set_consumer_name(ts->int_gpiod, "BU21013 INT");

	/* configure the touch panel controller */
	error = bu21013_init_chip(ts);
	if (error) {
		dev_err(&client->dev, "error in bu21013 config\n");
		return error;
	}

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, bu21013_gpio_irq,
					  IRQF_ONESHOT, DRIVER_TP, ts);
	if (error) {
		dev_err(&client->dev, "request irq %d failed\n",
			client->irq);
		return error;
	}

	error = input_register_device(in_dev);
	if (error) {
		dev_err(&client->dev, "failed to register input device\n");
		return error;
	}

	i2c_set_clientdata(client, ts);

	return 0;
}