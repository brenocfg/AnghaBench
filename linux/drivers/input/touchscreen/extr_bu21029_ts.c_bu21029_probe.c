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
struct TYPE_2__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct bu21029_ts_data {int /*<<< orphan*/  prop; int /*<<< orphan*/  timer; struct input_dev* in_dev; struct i2c_client* client; int /*<<< orphan*/  reset_gpios; int /*<<< orphan*/  vdd; int /*<<< orphan*/  x_plate_ohms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EIO ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_12BIT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bu21029_start_chip ; 
 int /*<<< orphan*/  bu21029_stop_chip ; 
 int /*<<< orphan*/  bu21029_touch_release ; 
 int /*<<< orphan*/  bu21029_touch_soft_irq ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct bu21029_ts_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bu21029_ts_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bu21029_ts_data*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct bu21029_ts_data*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bu21029_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct bu21029_ts_data *bu21029;
	struct input_dev *in_dev;
	int error;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) {
		dev_err(&client->dev,
			"i2c functionality support is not sufficient\n");
		return -EIO;
	}

	bu21029 = devm_kzalloc(&client->dev, sizeof(*bu21029), GFP_KERNEL);
	if (!bu21029)
		return -ENOMEM;

	error = device_property_read_u32(&client->dev, "rohm,x-plate-ohms",
					 &bu21029->x_plate_ohms);
	if (error) {
		dev_err(&client->dev,
			"invalid 'x-plate-ohms' supplied: %d\n", error);
		return error;
	}

	bu21029->vdd = devm_regulator_get(&client->dev, "vdd");
	if (IS_ERR(bu21029->vdd)) {
		error = PTR_ERR(bu21029->vdd);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to acquire 'vdd' supply: %d\n", error);
		return error;
	}

	bu21029->reset_gpios = devm_gpiod_get_optional(&client->dev,
						       "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(bu21029->reset_gpios)) {
		error = PTR_ERR(bu21029->reset_gpios);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to acquire 'reset' gpio: %d\n", error);
		return error;
	}

	in_dev = devm_input_allocate_device(&client->dev);
	if (!in_dev) {
		dev_err(&client->dev, "unable to allocate input device\n");
		return -ENOMEM;
	}

	bu21029->client = client;
	bu21029->in_dev = in_dev;
	timer_setup(&bu21029->timer, bu21029_touch_release, 0);

	in_dev->name		= DRIVER_NAME;
	in_dev->id.bustype	= BUS_I2C;
	in_dev->open		= bu21029_start_chip;
	in_dev->close		= bu21029_stop_chip;

	input_set_capability(in_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_params(in_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_abs_params(in_dev, ABS_Y, 0, MAX_12BIT, 0, 0);
	input_set_abs_params(in_dev, ABS_PRESSURE, 0, MAX_12BIT, 0, 0);
	touchscreen_parse_properties(in_dev, false, &bu21029->prop);

	input_set_drvdata(in_dev, bu21029);

	irq_set_status_flags(client->irq, IRQ_NOAUTOEN);
	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, bu21029_touch_soft_irq,
					  IRQF_ONESHOT, DRIVER_NAME, bu21029);
	if (error) {
		dev_err(&client->dev,
			"unable to request touch irq: %d\n", error);
		return error;
	}

	error = input_register_device(in_dev);
	if (error) {
		dev_err(&client->dev,
			"unable to register input device: %d\n", error);
		return error;
	}

	i2c_set_clientdata(client, bu21029);

	return 0;
}