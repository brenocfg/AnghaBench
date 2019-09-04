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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct bu21013_ts_data {int touch_stopped; struct bu21013_platform_device const* regulator; int /*<<< orphan*/  irq; int /*<<< orphan*/  wait; struct i2c_client* client; struct bu21013_platform_device const* chip; struct input_dev* in_dev; } ;
struct bu21013_platform_device {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  touch_y_max; int /*<<< orphan*/  touch_x_max; int /*<<< orphan*/  cs_pin; int /*<<< orphan*/  touch_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  DRIVER_TP ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (struct bu21013_platform_device const*) ; 
 int PTR_ERR (struct bu21013_platform_device const*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bu21013_cs_disable (struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  bu21013_free_irq (struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  bu21013_gpio_irq ; 
 int bu21013_init_chip (struct bu21013_ts_data*) ; 
 struct bu21013_platform_device* bu21013_parse_dt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct bu21013_platform_device* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  kfree (struct bu21013_ts_data*) ; 
 struct bu21013_ts_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (struct bu21013_platform_device const*) ; 
 int regulator_enable (struct bu21013_platform_device const*) ; 
 struct bu21013_platform_device const* regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regulator_put (struct bu21013_platform_device const*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct bu21013_ts_data*) ; 

__attribute__((used)) static int bu21013_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	const struct bu21013_platform_device *pdata =
					dev_get_platdata(&client->dev);
	struct bu21013_ts_data *bu21013_data;
	struct input_dev *in_dev;
	int error;

	if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "i2c smbus byte data not supported\n");
		return -EIO;
	}

	if (!pdata) {
		pdata = bu21013_parse_dt(&client->dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}

	if (!gpio_is_valid(pdata->touch_pin)) {
		dev_err(&client->dev, "invalid touch_pin supplied\n");
		return -EINVAL;
	}

	bu21013_data = kzalloc(sizeof(struct bu21013_ts_data), GFP_KERNEL);
	in_dev = input_allocate_device();
	if (!bu21013_data || !in_dev) {
		dev_err(&client->dev, "device memory alloc failed\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	bu21013_data->in_dev = in_dev;
	bu21013_data->chip = pdata;
	bu21013_data->client = client;
	bu21013_data->irq = gpio_to_irq(pdata->touch_pin);

	bu21013_data->regulator = regulator_get(&client->dev, "avdd");
	if (IS_ERR(bu21013_data->regulator)) {
		dev_err(&client->dev, "regulator_get failed\n");
		error = PTR_ERR(bu21013_data->regulator);
		goto err_free_mem;
	}

	error = regulator_enable(bu21013_data->regulator);
	if (error < 0) {
		dev_err(&client->dev, "regulator enable failed\n");
		goto err_put_regulator;
	}

	bu21013_data->touch_stopped = false;
	init_waitqueue_head(&bu21013_data->wait);

	/* configure the gpio pins */
	error = gpio_request_one(pdata->cs_pin, GPIOF_OUT_INIT_HIGH,
				 "touchp_reset");
	if (error < 0) {
		dev_err(&client->dev, "Unable to request gpio reset_pin\n");
		goto err_disable_regulator;
	}

	/* configure the touch panel controller */
	error = bu21013_init_chip(bu21013_data);
	if (error) {
		dev_err(&client->dev, "error in bu21013 config\n");
		goto err_cs_disable;
	}

	/* register the device to input subsystem */
	in_dev->name = DRIVER_TP;
	in_dev->id.bustype = BUS_I2C;
	in_dev->dev.parent = &client->dev;

	__set_bit(EV_SYN, in_dev->evbit);
	__set_bit(EV_KEY, in_dev->evbit);
	__set_bit(EV_ABS, in_dev->evbit);

	input_set_abs_params(in_dev, ABS_MT_POSITION_X, 0,
						pdata->touch_x_max, 0, 0);
	input_set_abs_params(in_dev, ABS_MT_POSITION_Y, 0,
						pdata->touch_y_max, 0, 0);
	input_set_drvdata(in_dev, bu21013_data);

	error = request_threaded_irq(bu21013_data->irq, NULL, bu21013_gpio_irq,
				     IRQF_TRIGGER_FALLING | IRQF_SHARED |
					IRQF_ONESHOT,
				     DRIVER_TP, bu21013_data);
	if (error) {
		dev_err(&client->dev, "request irq %d failed\n",
			bu21013_data->irq);
		goto err_cs_disable;
	}

	error = input_register_device(in_dev);
	if (error) {
		dev_err(&client->dev, "failed to register input device\n");
		goto err_free_irq;
	}

	device_init_wakeup(&client->dev, pdata->wakeup);
	i2c_set_clientdata(client, bu21013_data);

	return 0;

err_free_irq:
	bu21013_free_irq(bu21013_data);
err_cs_disable:
	bu21013_cs_disable(bu21013_data);
err_disable_regulator:
	regulator_disable(bu21013_data->regulator);
err_put_regulator:
	regulator_put(bu21013_data->regulator);
err_free_mem:
	input_free_device(in_dev);
	kfree(bu21013_data);

	return error;
}