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
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_2__ dev; int /*<<< orphan*/  (* close ) (struct input_dev*) ;int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct icn8318_data {struct input_dev* input; struct i2c_client* client; int /*<<< orphan*/  prop; int /*<<< orphan*/  wake_gpio; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  ICN8318_MAX_TOUCHES ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct icn8318_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct icn8318_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct icn8318_data*) ; 
 int /*<<< orphan*/  icn8318_irq ; 
 int /*<<< orphan*/  icn8318_start ; 
 int /*<<< orphan*/  icn8318_stop (struct input_dev*) ; 
 int /*<<< orphan*/  input_abs_get_max (struct input_dev*,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct icn8318_data*) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int icn8318_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct icn8318_data *data;
	struct input_dev *input;
	int error;

	if (!client->irq) {
		dev_err(dev, "Error no irq specified\n");
		return -EINVAL;
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->wake_gpio = devm_gpiod_get(dev, "wake", GPIOD_OUT_LOW);
	if (IS_ERR(data->wake_gpio)) {
		error = PTR_ERR(data->wake_gpio);
		if (error != -EPROBE_DEFER)
			dev_err(dev, "Error getting wake gpio: %d\n", error);
		return error;
	}

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->open = icn8318_start;
	input->close = icn8318_stop;
	input->dev.parent = dev;

	input_set_capability(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input, EV_ABS, ABS_MT_POSITION_Y);

	touchscreen_parse_properties(input, true, &data->prop);
	if (!input_abs_get_max(input, ABS_MT_POSITION_X) ||
	    !input_abs_get_max(input, ABS_MT_POSITION_Y)) {
		dev_err(dev, "Error touchscreen-size-x and/or -y missing\n");
		return -EINVAL;
	}

	error = input_mt_init_slots(input, ICN8318_MAX_TOUCHES,
				    INPUT_MT_DIRECT | INPUT_MT_DROP_UNUSED);
	if (error)
		return error;

	data->client = client;
	data->input = input;
	input_set_drvdata(input, data);

	error = devm_request_threaded_irq(dev, client->irq, NULL, icn8318_irq,
					  IRQF_ONESHOT, client->name, data);
	if (error) {
		dev_err(dev, "Error requesting irq: %d\n", error);
		return error;
	}

	/* Stop device till opened */
	icn8318_stop(data->input);

	error = input_register_device(input);
	if (error)
		return error;

	i2c_set_clientdata(client, data);

	return 0;
}