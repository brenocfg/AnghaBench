#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int press_invert; int /*<<< orphan*/  baseval; int /*<<< orphan*/  pressbit; int /*<<< orphan*/  status_reg; } ;
struct mcs_touchkey_data {unsigned int* keycodes; int /*<<< orphan*/  (* poweron ) (int) ;TYPE_1__ chip; struct input_dev* input_dev; struct i2c_client* client; } ;
struct mcs_platform_data {int keymap_size; int /*<<< orphan*/  (* poweron ) (int) ;int /*<<< orphan*/  (* cfg_pin ) () ;int /*<<< orphan*/ * keymap; scalar_t__ key_maxval; int /*<<< orphan*/  no_autorepeat; } ;
struct TYPE_10__ {TYPE_5__* parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; unsigned int* keycode; int keycodesize; int /*<<< orphan*/  keybit; scalar_t__ keycodemax; int /*<<< orphan*/ * evbit; TYPE_3__ dev; TYPE_2__ id; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_12__ {TYPE_4__* driver; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_5__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ MCS5000_TOUCHKEY ; 
 int /*<<< orphan*/  MCS5000_TOUCHKEY_BASE_VAL ; 
 unsigned int MCS5000_TOUCHKEY_FW ; 
 int /*<<< orphan*/  MCS5000_TOUCHKEY_STATUS ; 
 int /*<<< orphan*/  MCS5000_TOUCHKEY_STATUS_PRESS ; 
 int /*<<< orphan*/  MCS5080_TOUCHKEY_BASE_VAL ; 
 unsigned int MCS5080_TOUCHKEY_FW ; 
 int /*<<< orphan*/  MCS5080_TOUCHKEY_STATUS ; 
 int /*<<< orphan*/  MCS5080_TOUCHKEY_STATUS_PRESS ; 
 unsigned int MCS_KEY_CODE (int /*<<< orphan*/ ) ; 
 unsigned int MCS_KEY_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 struct mcs_platform_data* dev_get_platdata (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mcs_touchkey_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mcs_touchkey_data*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,unsigned int) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct mcs_touchkey_data*) ; 
 int /*<<< orphan*/  keycodes ; 
 int /*<<< orphan*/  kfree (struct mcs_touchkey_data*) ; 
 struct mcs_touchkey_data* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs_touchkey_interrupt ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mcs_touchkey_data*) ; 
 int /*<<< orphan*/  struct_size (struct mcs_touchkey_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static int mcs_touchkey_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	const struct mcs_platform_data *pdata;
	struct mcs_touchkey_data *data;
	struct input_dev *input_dev;
	unsigned int fw_reg;
	int fw_ver;
	int error;
	int i;

	pdata = dev_get_platdata(&client->dev);
	if (!pdata) {
		dev_err(&client->dev, "no platform data defined\n");
		return -EINVAL;
	}

	data = kzalloc(struct_size(data, keycodes, pdata->key_maxval + 1),
		       GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!data || !input_dev) {
		dev_err(&client->dev, "Failed to allocate memory\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	data->client = client;
	data->input_dev = input_dev;

	if (id->driver_data == MCS5000_TOUCHKEY) {
		data->chip.status_reg = MCS5000_TOUCHKEY_STATUS;
		data->chip.pressbit = MCS5000_TOUCHKEY_STATUS_PRESS;
		data->chip.baseval = MCS5000_TOUCHKEY_BASE_VAL;
		fw_reg = MCS5000_TOUCHKEY_FW;
	} else {
		data->chip.status_reg = MCS5080_TOUCHKEY_STATUS;
		data->chip.pressbit = MCS5080_TOUCHKEY_STATUS_PRESS;
		data->chip.press_invert = 1;
		data->chip.baseval = MCS5080_TOUCHKEY_BASE_VAL;
		fw_reg = MCS5080_TOUCHKEY_FW;
	}

	fw_ver = i2c_smbus_read_byte_data(client, fw_reg);
	if (fw_ver < 0) {
		error = fw_ver;
		dev_err(&client->dev, "i2c read error[%d]\n", error);
		goto err_free_mem;
	}
	dev_info(&client->dev, "Firmware version: %d\n", fw_ver);

	input_dev->name = "MELFAS MCS Touchkey";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	if (!pdata->no_autorepeat)
		input_dev->evbit[0] |= BIT_MASK(EV_REP);
	input_dev->keycode = data->keycodes;
	input_dev->keycodesize = sizeof(data->keycodes[0]);
	input_dev->keycodemax = pdata->key_maxval + 1;

	for (i = 0; i < pdata->keymap_size; i++) {
		unsigned int val = MCS_KEY_VAL(pdata->keymap[i]);
		unsigned int code = MCS_KEY_CODE(pdata->keymap[i]);

		data->keycodes[val] = code;
		__set_bit(code, input_dev->keybit);
	}

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, data);

	if (pdata->cfg_pin)
		pdata->cfg_pin();

	if (pdata->poweron) {
		data->poweron = pdata->poweron;
		data->poweron(true);
	}

	error = request_threaded_irq(client->irq, NULL, mcs_touchkey_interrupt,
				     IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				     client->dev.driver->name, data);
	if (error) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		goto err_free_mem;
	}

	error = input_register_device(input_dev);
	if (error)
		goto err_free_irq;

	i2c_set_clientdata(client, data);
	return 0;

err_free_irq:
	free_irq(client->irq, data);
err_free_mem:
	input_free_device(input_dev);
	kfree(data);
	return error;
}