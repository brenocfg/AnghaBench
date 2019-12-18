#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
struct i2c_device_id {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_6__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;
struct elants_data {int keep_power_in_suspend; int x_max; int y_max; TYPE_2__* input; int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; void* reset_gpio; void* vccio; void* vcc33; struct i2c_client* client; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  sysfs_mutex; } ;
struct TYPE_16__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_17__ {char* name; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int DEVICE_NAME ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  I2C_SMBUS_BYTE ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MAX_CONTACT_NUM ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_6__*,int) ; 
 int devm_add_action (TYPE_6__*,int /*<<< orphan*/  (*) (struct elants_data*),struct elants_data*) ; 
 int devm_device_add_group (TYPE_6__*,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_input_allocate_device (TYPE_6__*) ; 
 struct elants_data* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (TYPE_6__*,char*) ; 
 int devm_request_threaded_irq (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct elants_data*) ; 
 int /*<<< orphan*/  elants_attribute_group ; 
 int elants_i2c_initialize (struct elants_data*) ; 
 int /*<<< orphan*/  elants_i2c_irq ; 
 int /*<<< orphan*/  elants_i2c_power_off (struct elants_data*) ; 
 int elants_i2c_power_on (struct elants_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct elants_data*) ; 
 scalar_t__ i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_abs_set_res (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elants_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	union i2c_smbus_data dummy;
	struct elants_data *ts;
	unsigned long irqflags;
	int error;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev,
			"%s: i2c check functionality error\n", DEVICE_NAME);
		return -ENXIO;
	}

	ts = devm_kzalloc(&client->dev, sizeof(struct elants_data), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	mutex_init(&ts->sysfs_mutex);
	init_completion(&ts->cmd_done);

	ts->client = client;
	i2c_set_clientdata(client, ts);

	ts->vcc33 = devm_regulator_get(&client->dev, "vcc33");
	if (IS_ERR(ts->vcc33)) {
		error = PTR_ERR(ts->vcc33);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'vcc33' regulator: %d\n",
				error);
		return error;
	}

	ts->vccio = devm_regulator_get(&client->dev, "vccio");
	if (IS_ERR(ts->vccio)) {
		error = PTR_ERR(ts->vccio);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'vccio' regulator: %d\n",
				error);
		return error;
	}

	ts->reset_gpio = devm_gpiod_get(&client->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ts->reset_gpio)) {
		error = PTR_ERR(ts->reset_gpio);

		if (error == -EPROBE_DEFER)
			return error;

		if (error != -ENOENT && error != -ENOSYS) {
			dev_err(&client->dev,
				"failed to get reset gpio: %d\n",
				error);
			return error;
		}

		ts->keep_power_in_suspend = true;
	}

	error = elants_i2c_power_on(ts);
	if (error)
		return error;

	error = devm_add_action(&client->dev, elants_i2c_power_off, ts);
	if (error) {
		dev_err(&client->dev,
			"failed to install power off action: %d\n", error);
		elants_i2c_power_off(ts);
		return error;
	}

	/* Make sure there is something at this address */
	if (i2c_smbus_xfer(client->adapter, client->addr, 0,
			   I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0) {
		dev_err(&client->dev, "nothing at this address\n");
		return -ENXIO;
	}

	error = elants_i2c_initialize(ts);
	if (error) {
		dev_err(&client->dev, "failed to initialize: %d\n", error);
		return error;
	}

	ts->input = devm_input_allocate_device(&client->dev);
	if (!ts->input) {
		dev_err(&client->dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	ts->input->name = "Elan Touchscreen";
	ts->input->id.bustype = BUS_I2C;

	__set_bit(BTN_TOUCH, ts->input->keybit);
	__set_bit(EV_ABS, ts->input->evbit);
	__set_bit(EV_KEY, ts->input->evbit);

	/* Single touch input params setup */
	input_set_abs_params(ts->input, ABS_X, 0, ts->x_max, 0, 0);
	input_set_abs_params(ts->input, ABS_Y, 0, ts->y_max, 0, 0);
	input_set_abs_params(ts->input, ABS_PRESSURE, 0, 255, 0, 0);
	input_abs_set_res(ts->input, ABS_X, ts->x_res);
	input_abs_set_res(ts->input, ABS_Y, ts->y_res);

	/* Multitouch input params setup */
	error = input_mt_init_slots(ts->input, MAX_CONTACT_NUM,
				    INPUT_MT_DIRECT | INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(&client->dev,
			"failed to initialize MT slots: %d\n", error);
		return error;
	}

	input_set_abs_params(ts->input, ABS_MT_POSITION_X, 0, ts->x_max, 0, 0);
	input_set_abs_params(ts->input, ABS_MT_POSITION_Y, 0, ts->y_max, 0, 0);
	input_set_abs_params(ts->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(ts->input, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_abs_set_res(ts->input, ABS_MT_POSITION_X, ts->x_res);
	input_abs_set_res(ts->input, ABS_MT_POSITION_Y, ts->y_res);

	error = input_register_device(ts->input);
	if (error) {
		dev_err(&client->dev,
			"unable to register input device: %d\n", error);
		return error;
	}

	/*
	 * Platform code (ACPI, DTS) should normally set up interrupt
	 * for us, but in case it did not let's fall back to using falling
	 * edge to be compatible with older Chromebooks.
	 */
	irqflags = irq_get_trigger_type(client->irq);
	if (!irqflags)
		irqflags = IRQF_TRIGGER_FALLING;

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, elants_i2c_irq,
					  irqflags | IRQF_ONESHOT,
					  client->name, ts);
	if (error) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return error;
	}

	/*
	 * Systems using device tree should set up wakeup via DTS,
	 * the rest will configure device as wakeup source by default.
	 */
	if (!client->dev.of_node)
		device_init_wakeup(&client->dev, true);

	error = devm_device_add_group(&client->dev, &elants_attribute_group);
	if (error) {
		dev_err(&client->dev, "failed to create sysfs attributes: %d\n",
			error);
		return error;
	}

	return 0;
}