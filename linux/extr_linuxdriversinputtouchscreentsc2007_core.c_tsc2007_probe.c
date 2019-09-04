#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct tsc2007_platform_data {int /*<<< orphan*/  (* init_platform_hw ) () ;scalar_t__ exit_platform_hw; } ;
struct tsc2007 {int /*<<< orphan*/  irq; int /*<<< orphan*/  fuzzz; int /*<<< orphan*/  fuzzy; int /*<<< orphan*/  fuzzx; int /*<<< orphan*/  phys; int /*<<< orphan*/  mlock; int /*<<< orphan*/  wait; struct input_dev* input; struct i2c_client* client; } ;
struct TYPE_11__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {TYPE_2__* driver; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  MAX_12BIT ; 
 int /*<<< orphan*/  PWRDOWN ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int,...) ; 
 struct tsc2007_platform_data* dev_get_platdata (TYPE_3__*) ; 
 char* dev_name (TYPE_3__*) ; 
 int devm_add_action (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 struct tsc2007* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tsc2007*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tsc2007*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct tsc2007*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  tsc2007_call_exit_platform_hw ; 
 int /*<<< orphan*/  tsc2007_close ; 
 int /*<<< orphan*/  tsc2007_hard_irq ; 
 int tsc2007_iio_configure (struct tsc2007*) ; 
 int /*<<< orphan*/  tsc2007_open ; 
 int tsc2007_probe_dt (struct i2c_client*,struct tsc2007*) ; 
 int tsc2007_probe_pdev (struct i2c_client*,struct tsc2007*,struct tsc2007_platform_data const*,struct i2c_device_id const*) ; 
 int /*<<< orphan*/  tsc2007_soft_irq ; 
 int /*<<< orphan*/  tsc2007_stop (struct tsc2007*) ; 
 int tsc2007_xfer (struct tsc2007*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsc2007_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	const struct tsc2007_platform_data *pdata =
		dev_get_platdata(&client->dev);
	struct tsc2007 *ts;
	struct input_dev *input_dev;
	int err;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		return -EIO;

	ts = devm_kzalloc(&client->dev, sizeof(struct tsc2007), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	if (pdata)
		err = tsc2007_probe_pdev(client, ts, pdata, id);
	else
		err = tsc2007_probe_dt(client, ts);
	if (err)
		return err;

	input_dev = devm_input_allocate_device(&client->dev);
	if (!input_dev)
		return -ENOMEM;

	i2c_set_clientdata(client, ts);

	ts->client = client;
	ts->irq = client->irq;
	ts->input = input_dev;

	init_waitqueue_head(&ts->wait);
	mutex_init(&ts->mlock);

	snprintf(ts->phys, sizeof(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev->name = "TSC2007 Touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->open = tsc2007_open;
	input_dev->close = tsc2007_close;

	input_set_drvdata(input_dev, ts);

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);

	input_set_abs_params(input_dev, ABS_X, 0, MAX_12BIT, ts->fuzzx, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, MAX_12BIT, ts->fuzzy, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, MAX_12BIT,
			     ts->fuzzz, 0);

	if (pdata) {
		if (pdata->exit_platform_hw) {
			err = devm_add_action(&client->dev,
					      tsc2007_call_exit_platform_hw,
					      &client->dev);
			if (err) {
				dev_err(&client->dev,
					"Failed to register exit_platform_hw action, %d\n",
					err);
				return err;
			}
		}

		if (pdata->init_platform_hw)
			pdata->init_platform_hw();
	}

	err = devm_request_threaded_irq(&client->dev, ts->irq,
					tsc2007_hard_irq, tsc2007_soft_irq,
					IRQF_ONESHOT,
					client->dev.driver->name, ts);
	if (err) {
		dev_err(&client->dev, "Failed to request irq %d: %d\n",
			ts->irq, err);
		return err;
	}

	tsc2007_stop(ts);

	/* power down the chip (TSC2007_SETUP does not ACK on I2C) */
	err = tsc2007_xfer(ts, PWRDOWN);
	if (err < 0) {
		dev_err(&client->dev,
			"Failed to setup chip: %d\n", err);
		return err;	/* chip does not respond */
	}

	err = input_register_device(input_dev);
	if (err) {
		dev_err(&client->dev,
			"Failed to register input device: %d\n", err);
		return err;
	}

	err =  tsc2007_iio_configure(ts);
	if (err) {
		dev_err(&client->dev,
			"Failed to register with IIO: %d\n", err);
		return err;
	}

	return 0;
}