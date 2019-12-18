#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct stmfts_data {int /*<<< orphan*/ * ledvdd; scalar_t__ use_key; TYPE_2__* input; int /*<<< orphan*/  prop; TYPE_8__* regulators; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  mutex; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct TYPE_13__ {char* supply; } ;
struct TYPE_11__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_12__ {int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_8__*) ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  KEY_BACK ; 
 int /*<<< orphan*/  KEY_MENU ; 
 int /*<<< orphan*/  STMFTS_DEV_NAME ; 
 int /*<<< orphan*/  STMFTS_MAX_FINGERS ; 
 size_t STMFTS_REGULATOR_AVDD ; 
 size_t STMFTS_REGULATOR_VDD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (int /*<<< orphan*/ *) ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stmfts_data*) ; 
 int devm_device_add_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct stmfts_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct stmfts_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct stmfts_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int input_mt_init_slots (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct stmfts_data*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmfts_attribute_group ; 
 int stmfts_enable_led (struct stmfts_data*) ; 
 int /*<<< orphan*/  stmfts_input_close ; 
 int /*<<< orphan*/  stmfts_input_open ; 
 int /*<<< orphan*/  stmfts_irq_handler ; 
 int /*<<< orphan*/  stmfts_power_off ; 
 int stmfts_power_on (struct stmfts_data*) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stmfts_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int err;
	struct stmfts_data *sdata;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
						I2C_FUNC_SMBUS_BYTE_DATA |
						I2C_FUNC_SMBUS_I2C_BLOCK))
		return -ENODEV;

	sdata = devm_kzalloc(&client->dev, sizeof(*sdata), GFP_KERNEL);
	if (!sdata)
		return -ENOMEM;

	i2c_set_clientdata(client, sdata);

	sdata->client = client;
	mutex_init(&sdata->mutex);
	init_completion(&sdata->cmd_done);

	sdata->regulators[STMFTS_REGULATOR_VDD].supply = "vdd";
	sdata->regulators[STMFTS_REGULATOR_AVDD].supply = "avdd";
	err = devm_regulator_bulk_get(&client->dev,
				      ARRAY_SIZE(sdata->regulators),
				      sdata->regulators);
	if (err)
		return err;

	sdata->input = devm_input_allocate_device(&client->dev);
	if (!sdata->input)
		return -ENOMEM;

	sdata->input->name = STMFTS_DEV_NAME;
	sdata->input->id.bustype = BUS_I2C;
	sdata->input->open = stmfts_input_open;
	sdata->input->close = stmfts_input_close;

	input_set_capability(sdata->input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(sdata->input, EV_ABS, ABS_MT_POSITION_Y);
	touchscreen_parse_properties(sdata->input, true, &sdata->prop);

	input_set_abs_params(sdata->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(sdata->input, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
	input_set_abs_params(sdata->input, ABS_MT_ORIENTATION, 0, 255, 0, 0);
	input_set_abs_params(sdata->input, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_set_abs_params(sdata->input, ABS_DISTANCE, 0, 255, 0, 0);

	sdata->use_key = device_property_read_bool(&client->dev,
						   "touch-key-connected");
	if (sdata->use_key) {
		input_set_capability(sdata->input, EV_KEY, KEY_MENU);
		input_set_capability(sdata->input, EV_KEY, KEY_BACK);
	}

	err = input_mt_init_slots(sdata->input,
				  STMFTS_MAX_FINGERS, INPUT_MT_DIRECT);
	if (err)
		return err;

	input_set_drvdata(sdata->input, sdata);

	/*
	 * stmfts_power_on expects interrupt to be disabled, but
	 * at this point the device is still off and I do not trust
	 * the status of the irq line that can generate some spurious
	 * interrupts. To be on the safe side it's better to not enable
	 * the interrupts during their request.
	 */
	irq_set_status_flags(client->irq, IRQ_NOAUTOEN);
	err = devm_request_threaded_irq(&client->dev, client->irq,
					NULL, stmfts_irq_handler,
					IRQF_ONESHOT,
					"stmfts_irq", sdata);
	if (err)
		return err;

	dev_dbg(&client->dev, "initializing ST-Microelectronics FTS...\n");

	err = stmfts_power_on(sdata);
	if (err)
		return err;

	err = devm_add_action_or_reset(&client->dev, stmfts_power_off, sdata);
	if (err)
		return err;

	err = input_register_device(sdata->input);
	if (err)
		return err;

	if (sdata->use_key) {
		err = stmfts_enable_led(sdata);
		if (err) {
			/*
			 * Even if the LEDs have failed to be initialized and
			 * used in the driver, I can still use the device even
			 * without LEDs. The ledvdd regulator pointer will be
			 * used as a flag.
			 */
			dev_warn(&client->dev, "unable to use touchkey leds\n");
			sdata->ledvdd = NULL;
		}
	}

	err = devm_device_add_group(&client->dev, &stmfts_attribute_group);
	if (err)
		return err;

	pm_runtime_enable(&client->dev);
	device_enable_async_suspend(&client->dev);

	return 0;
}