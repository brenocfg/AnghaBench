#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct goodix_ts_data {int /*<<< orphan*/  cfg_name; int /*<<< orphan*/  id; scalar_t__ gpiod_rst; scalar_t__ gpiod_int; int /*<<< orphan*/  chip; int /*<<< orphan*/  avdd28; int /*<<< orphan*/  vddio; int /*<<< orphan*/  contact_size; int /*<<< orphan*/  firmware_loading_complete; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOODIX_CONTACT_SIZE ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct goodix_ts_data*) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct goodix_ts_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goodix_config_cb ; 
 int goodix_configure_dev (struct goodix_ts_data*) ; 
 int /*<<< orphan*/  goodix_disable_regulators ; 
 int /*<<< orphan*/  goodix_get_chip_data (int /*<<< orphan*/ ) ; 
 int goodix_get_gpio_config (struct goodix_ts_data*) ; 
 int goodix_i2c_test (struct i2c_client*) ; 
 int goodix_read_version (struct goodix_ts_data*) ; 
 int goodix_reset (struct goodix_ts_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct goodix_ts_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct goodix_ts_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goodix_ts_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct goodix_ts_data *ts;
	int error;

	dev_dbg(&client->dev, "I2C Address: 0x%02x\n", client->addr);

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C check functionality failed.\n");
		return -ENXIO;
	}

	ts = devm_kzalloc(&client->dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	ts->client = client;
	i2c_set_clientdata(client, ts);
	init_completion(&ts->firmware_loading_complete);
	ts->contact_size = GOODIX_CONTACT_SIZE;

	error = goodix_get_gpio_config(ts);
	if (error)
		return error;

	/* power up the controller */
	error = regulator_enable(ts->avdd28);
	if (error) {
		dev_err(&client->dev,
			"Failed to enable AVDD28 regulator: %d\n",
			error);
		return error;
	}

	error = regulator_enable(ts->vddio);
	if (error) {
		dev_err(&client->dev,
			"Failed to enable VDDIO regulator: %d\n",
			error);
		regulator_disable(ts->avdd28);
		return error;
	}

	error = devm_add_action_or_reset(&client->dev,
					 goodix_disable_regulators, ts);
	if (error)
		return error;

	if (ts->gpiod_int && ts->gpiod_rst) {
		/* reset the controller */
		error = goodix_reset(ts);
		if (error) {
			dev_err(&client->dev, "Controller reset failed.\n");
			return error;
		}
	}

	error = goodix_i2c_test(client);
	if (error) {
		dev_err(&client->dev, "I2C communication failure: %d\n", error);
		return error;
	}

	error = goodix_read_version(ts);
	if (error) {
		dev_err(&client->dev, "Read version failed.\n");
		return error;
	}

	ts->chip = goodix_get_chip_data(ts->id);

	if (ts->gpiod_int && ts->gpiod_rst) {
		/* update device config */
		ts->cfg_name = devm_kasprintf(&client->dev, GFP_KERNEL,
					      "goodix_%d_cfg.bin", ts->id);
		if (!ts->cfg_name)
			return -ENOMEM;

		error = request_firmware_nowait(THIS_MODULE, true, ts->cfg_name,
						&client->dev, GFP_KERNEL, ts,
						goodix_config_cb);
		if (error) {
			dev_err(&client->dev,
				"Failed to invoke firmware loader: %d\n",
				error);
			return error;
		}

		return 0;
	} else {
		error = goodix_configure_dev(ts);
		if (error)
			return error;
	}

	return 0;
}