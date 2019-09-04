#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct st1232_ts_data {char* reset_gpio; struct input_dev* input_dev; struct i2c_client* client; } ;
struct TYPE_10__ {TYPE_3__* parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  MAX_AREA ; 
 int /*<<< orphan*/  MAX_X ; 
 int /*<<< orphan*/  MAX_Y ; 
 int /*<<< orphan*/  MIN_X ; 
 int /*<<< orphan*/  MIN_Y ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 int devm_gpio_request (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 struct st1232_ts_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct st1232_ts_data*) ; 
 scalar_t__ gpio_is_valid (char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct st1232_ts_data*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* of_get_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st1232_ts_irq_handler ; 
 int /*<<< orphan*/  st1232_ts_power (struct st1232_ts_data*,int) ; 

__attribute__((used)) static int st1232_ts_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct st1232_ts_data *ts;
	struct input_dev *input_dev;
	int error;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "need I2C_FUNC_I2C\n");
		return -EIO;
	}

	if (!client->irq) {
		dev_err(&client->dev, "no IRQ?\n");
		return -EINVAL;
	}

	ts = devm_kzalloc(&client->dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	input_dev = devm_input_allocate_device(&client->dev);
	if (!input_dev)
		return -ENOMEM;

	ts->client = client;
	ts->input_dev = input_dev;

	ts->reset_gpio = of_get_gpio(client->dev.of_node, 0);
	if (gpio_is_valid(ts->reset_gpio)) {
		error = devm_gpio_request(&client->dev, ts->reset_gpio, NULL);
		if (error) {
			dev_err(&client->dev,
				"Unable to request GPIO pin %d.\n",
				ts->reset_gpio);
				return error;
		}
	}

	st1232_ts_power(ts, true);

	input_dev->name = "st1232-touchscreen";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	__set_bit(EV_SYN, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);

	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, MAX_AREA, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, MIN_X, MAX_X, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, MIN_Y, MAX_Y, 0, 0);

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, st1232_ts_irq_handler,
					  IRQF_ONESHOT,
					  client->name, ts);
	if (error) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return error;
	}

	error = input_register_device(ts->input_dev);
	if (error) {
		dev_err(&client->dev, "Unable to register %s input device\n",
			input_dev->name);
		return error;
	}

	i2c_set_clientdata(client, ts);
	device_init_wakeup(&client->dev, 1);

	return 0;
}