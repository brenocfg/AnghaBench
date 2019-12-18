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
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct auo_pixcir_ts_platdata {int x_max; int y_max; int /*<<< orphan*/  int_setting; int /*<<< orphan*/  gpio_rst; int /*<<< orphan*/  gpio_int; } ;
struct auo_pixcir_ts {int stopped; struct input_dev* input; int /*<<< orphan*/  phys; int /*<<< orphan*/  wait; scalar_t__ touch_ind_mode; struct i2c_client* client; struct auo_pixcir_ts_platdata const* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int AUO_PIXCIR_MAX_AREA ; 
 int /*<<< orphan*/  AUO_PIXCIR_REG_VERSION ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOF_DIR_IN ; 
 int GPIOF_DIR_OUT ; 
 int GPIOF_INIT_HIGH ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct auo_pixcir_ts_platdata const*) ; 
 int PTR_ERR (struct auo_pixcir_ts_platdata const*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auo_pixcir_input_close ; 
 int /*<<< orphan*/  auo_pixcir_input_open ; 
 int auo_pixcir_int_config (struct auo_pixcir_ts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auo_pixcir_interrupt ; 
 struct auo_pixcir_ts_platdata* auo_pixcir_parse_dt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auo_pixcir_reset ; 
 int auo_pixcir_stop (struct auo_pixcir_ts*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct auo_pixcir_ts_platdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct auo_pixcir_ts*) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct auo_pixcir_ts* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct auo_pixcir_ts*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct auo_pixcir_ts*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct auo_pixcir_ts*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int auo_pixcir_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	const struct auo_pixcir_ts_platdata *pdata;
	struct auo_pixcir_ts *ts;
	struct input_dev *input_dev;
	int version;
	int error;

	pdata = dev_get_platdata(&client->dev);
	if (!pdata) {
		pdata = auo_pixcir_parse_dt(&client->dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}

	ts = devm_kzalloc(&client->dev,
			  sizeof(struct auo_pixcir_ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	input_dev = devm_input_allocate_device(&client->dev);
	if (!input_dev) {
		dev_err(&client->dev, "could not allocate input device\n");
		return -ENOMEM;
	}

	ts->pdata = pdata;
	ts->client = client;
	ts->input = input_dev;
	ts->touch_ind_mode = 0;
	ts->stopped = true;
	init_waitqueue_head(&ts->wait);

	snprintf(ts->phys, sizeof(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev->name = "AUO-Pixcir touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->open = auo_pixcir_input_open;
	input_dev->close = auo_pixcir_input_close;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);

	__set_bit(BTN_TOUCH, input_dev->keybit);

	/* For single touch */
	input_set_abs_params(input_dev, ABS_X, 0, pdata->x_max, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, pdata->y_max, 0, 0);

	/* For multi touch */
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0,
			     pdata->x_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0,
			     pdata->y_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
			     AUO_PIXCIR_MAX_AREA, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MINOR, 0,
			     AUO_PIXCIR_MAX_AREA, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);

	input_set_drvdata(ts->input, ts);

	error = devm_gpio_request_one(&client->dev, pdata->gpio_int,
				      GPIOF_DIR_IN, "auo_pixcir_ts_int");
	if (error) {
		dev_err(&client->dev, "request of gpio %d failed, %d\n",
			pdata->gpio_int, error);
		return error;
	}

	error = devm_gpio_request_one(&client->dev, pdata->gpio_rst,
				      GPIOF_DIR_OUT | GPIOF_INIT_HIGH,
				      "auo_pixcir_ts_rst");
	if (error) {
		dev_err(&client->dev, "request of gpio %d failed, %d\n",
			pdata->gpio_rst, error);
		return error;
	}

	error = devm_add_action_or_reset(&client->dev, auo_pixcir_reset, ts);
	if (error) {
		dev_err(&client->dev, "failed to register reset action, %d\n",
			error);
		return error;
	}

	msleep(200);

	version = i2c_smbus_read_byte_data(client, AUO_PIXCIR_REG_VERSION);
	if (version < 0) {
		error = version;
		return error;
	}

	dev_info(&client->dev, "firmware version 0x%X\n", version);

	error = auo_pixcir_int_config(ts, pdata->int_setting);
	if (error)
		return error;

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, auo_pixcir_interrupt,
					  IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					  input_dev->name, ts);
	if (error) {
		dev_err(&client->dev, "irq %d requested failed, %d\n",
			client->irq, error);
		return error;
	}

	/* stop device and put it into deep sleep until it is opened */
	error = auo_pixcir_stop(ts);
	if (error)
		return error;

	error = input_register_device(input_dev);
	if (error) {
		dev_err(&client->dev, "could not register input device, %d\n",
			error);
		return error;
	}

	i2c_set_clientdata(client, ts);

	return 0;
}