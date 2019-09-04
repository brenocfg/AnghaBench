#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
struct TYPE_9__ {int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; int /*<<< orphan*/  y_max; int /*<<< orphan*/  x_max; } ;
struct raydium_data {TYPE_3__* input; TYPE_2__ info; int /*<<< orphan*/  report_data; int /*<<< orphan*/  pkg_size; void* reset_gpio; void* vccio; void* avdd; struct i2c_client* client; int /*<<< orphan*/  sysfs_mutex; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_10__ {char* name; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  I2C_SMBUS_BYTE ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  RM_MAX_TOUCH_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_add_action (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct raydium_data*),struct raydium_data*) ; 
 int devm_device_add_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kmalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct raydium_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct raydium_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct raydium_data*) ; 
 scalar_t__ i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  input_abs_set_res (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raydium_i2c_attribute_group ; 
 int raydium_i2c_initialize (struct raydium_data*) ; 
 int /*<<< orphan*/  raydium_i2c_irq ; 
 int /*<<< orphan*/  raydium_i2c_power_off (struct raydium_data*) ; 
 int raydium_i2c_power_on (struct raydium_data*) ; 

__attribute__((used)) static int raydium_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	union i2c_smbus_data dummy;
	struct raydium_data *ts;
	int error;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev,
			"i2c check functionality error (need I2C_FUNC_I2C)\n");
		return -ENXIO;
	}

	ts = devm_kzalloc(&client->dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	mutex_init(&ts->sysfs_mutex);

	ts->client = client;
	i2c_set_clientdata(client, ts);

	ts->avdd = devm_regulator_get(&client->dev, "avdd");
	if (IS_ERR(ts->avdd)) {
		error = PTR_ERR(ts->avdd);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'avdd' regulator: %d\n", error);
		return error;
	}

	ts->vccio = devm_regulator_get(&client->dev, "vccio");
	if (IS_ERR(ts->vccio)) {
		error = PTR_ERR(ts->vccio);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get 'vccio' regulator: %d\n", error);
		return error;
	}

	ts->reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						 GPIOD_OUT_LOW);
	if (IS_ERR(ts->reset_gpio)) {
		error = PTR_ERR(ts->reset_gpio);
		if (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to get reset gpio: %d\n", error);
		return error;
	}

	error = raydium_i2c_power_on(ts);
	if (error)
		return error;

	error = devm_add_action(&client->dev, raydium_i2c_power_off, ts);
	if (error) {
		dev_err(&client->dev,
			"failed to install power off action: %d\n", error);
		raydium_i2c_power_off(ts);
		return error;
	}

	/* Make sure there is something at this address */
	if (i2c_smbus_xfer(client->adapter, client->addr, 0,
			   I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0) {
		dev_err(&client->dev, "nothing at this address\n");
		return -ENXIO;
	}

	error = raydium_i2c_initialize(ts);
	if (error) {
		dev_err(&client->dev, "failed to initialize: %d\n", error);
		return error;
	}

	ts->report_data = devm_kmalloc(&client->dev,
				       ts->pkg_size, GFP_KERNEL);
	if (!ts->report_data)
		return -ENOMEM;

	ts->input = devm_input_allocate_device(&client->dev);
	if (!ts->input) {
		dev_err(&client->dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	ts->input->name = "Raydium Touchscreen";
	ts->input->id.bustype = BUS_I2C;

	input_set_abs_params(ts->input, ABS_MT_POSITION_X,
			     0, le16_to_cpu(ts->info.x_max), 0, 0);
	input_set_abs_params(ts->input, ABS_MT_POSITION_Y,
			     0, le16_to_cpu(ts->info.y_max), 0, 0);
	input_abs_set_res(ts->input, ABS_MT_POSITION_X, ts->info.x_res);
	input_abs_set_res(ts->input, ABS_MT_POSITION_Y, ts->info.y_res);

	input_set_abs_params(ts->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(ts->input, ABS_MT_PRESSURE, 0, 255, 0, 0);

	error = input_mt_init_slots(ts->input, RM_MAX_TOUCH_NUM,
				    INPUT_MT_DIRECT | INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(&client->dev,
			"failed to initialize MT slots: %d\n", error);
		return error;
	}

	error = input_register_device(ts->input);
	if (error) {
		dev_err(&client->dev,
			"unable to register input device: %d\n", error);
		return error;
	}

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, raydium_i2c_irq,
					  IRQF_ONESHOT, client->name, ts);
	if (error) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return error;
	}

	error = devm_device_add_group(&client->dev,
				   &raydium_i2c_attribute_group);
	if (error) {
		dev_err(&client->dev, "failed to create sysfs attributes: %d\n",
			error);
		return error;
	}

	return 0;
}