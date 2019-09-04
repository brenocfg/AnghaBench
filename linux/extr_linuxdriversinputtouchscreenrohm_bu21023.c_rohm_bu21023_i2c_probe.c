#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rohm_ts_data {struct input_dev* input; int /*<<< orphan*/  setup2; struct i2c_client* client; } ;
struct TYPE_6__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_3__ id; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; TYPE_2__* adapter; struct device dev; } ;
struct TYPE_5__ {TYPE_1__* algo; } ;
struct TYPE_4__ {int /*<<< orphan*/  master_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BU21023_NAME ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_TRACK ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  MAF_1SAMPLE ; 
 int /*<<< orphan*/  MAX_CONTACTS ; 
 int /*<<< orphan*/  ROHM_TS_ABS_X_MAX ; 
 int /*<<< orphan*/  ROHM_TS_ABS_X_MIN ; 
 int /*<<< orphan*/  ROHM_TS_ABS_Y_MAX ; 
 int /*<<< orphan*/  ROHM_TS_ABS_Y_MIN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_device_add_group (struct device*,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct rohm_ts_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rohm_ts_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rohm_ts_data*) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct rohm_ts_data*) ; 
 int /*<<< orphan*/  rohm_ts_attr_group ; 
 int /*<<< orphan*/  rohm_ts_close ; 
 int /*<<< orphan*/  rohm_ts_open ; 
 int rohm_ts_power_off (struct i2c_client*) ; 
 int /*<<< orphan*/  rohm_ts_soft_irq ; 

__attribute__((used)) static int rohm_bu21023_i2c_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct rohm_ts_data *ts;
	struct input_dev *input;
	int error;

	if (!client->irq) {
		dev_err(dev, "IRQ is not assigned\n");
		return -EINVAL;
	}

	if (!client->adapter->algo->master_xfer) {
		dev_err(dev, "I2C level transfers not supported\n");
		return -EOPNOTSUPP;
	}

	/* Turn off CPU just in case */
	error = rohm_ts_power_off(client);
	if (error)
		return error;

	ts = devm_kzalloc(dev, sizeof(struct rohm_ts_data), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	ts->client = client;
	ts->setup2 = MAF_1SAMPLE;
	i2c_set_clientdata(client, ts);

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = BU21023_NAME;
	input->id.bustype = BUS_I2C;
	input->open = rohm_ts_open;
	input->close = rohm_ts_close;

	ts->input = input;
	input_set_drvdata(input, ts);

	input_set_abs_params(input, ABS_MT_POSITION_X,
			     ROHM_TS_ABS_X_MIN, ROHM_TS_ABS_X_MAX, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y,
			     ROHM_TS_ABS_Y_MIN, ROHM_TS_ABS_Y_MAX, 0, 0);

	error = input_mt_init_slots(input, MAX_CONTACTS,
				    INPUT_MT_DIRECT | INPUT_MT_TRACK |
				    INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(dev, "failed to multi touch slots initialization\n");
		return error;
	}

	error = devm_request_threaded_irq(dev, client->irq,
					  NULL, rohm_ts_soft_irq,
					  IRQF_ONESHOT, client->name, ts);
	if (error) {
		dev_err(dev, "failed to request IRQ: %d\n", error);
		return error;
	}

	error = input_register_device(input);
	if (error) {
		dev_err(dev, "failed to register input device: %d\n", error);
		return error;
	}

	error = devm_device_add_group(dev, &rohm_ts_attr_group);
	if (error) {
		dev_err(dev, "failed to create sysfs group: %d\n", error);
		return error;
	}

	return error;
}