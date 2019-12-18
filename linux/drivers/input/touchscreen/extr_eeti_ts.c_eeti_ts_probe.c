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
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; struct device dev; } ;
struct eeti_ts {int /*<<< orphan*/  attn_gpio; struct input_dev* input; struct i2c_client* client; int /*<<< orphan*/  props; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EETI_MAXVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct eeti_ts* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eeti_ts*) ; 
 int /*<<< orphan*/  eeti_ts_close ; 
 int /*<<< orphan*/  eeti_ts_isr ; 
 int /*<<< orphan*/  eeti_ts_open ; 
 int /*<<< orphan*/  eeti_ts_stop (struct eeti_ts*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct eeti_ts*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct eeti_ts*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eeti_ts_probe(struct i2c_client *client,
			 const struct i2c_device_id *idp)
{
	struct device *dev = &client->dev;
	struct eeti_ts *eeti;
	struct input_dev *input;
	int error;

	/*
	 * In contrast to what's described in the datasheet, there seems
	 * to be no way of probing the presence of that device using I2C
	 * commands. So we need to blindly believe it is there, and wait
	 * for interrupts to occur.
	 */

	eeti = devm_kzalloc(dev, sizeof(*eeti), GFP_KERNEL);
	if (!eeti) {
		dev_err(dev, "failed to allocate driver data\n");
		return -ENOMEM;
	}

	mutex_init(&eeti->mutex);

	input = devm_input_allocate_device(dev);
	if (!input) {
		dev_err(dev, "Failed to allocate input device.\n");
		return -ENOMEM;
	}

	input_set_capability(input, EV_KEY, BTN_TOUCH);

	input_set_abs_params(input, ABS_X, 0, EETI_MAXVAL, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, EETI_MAXVAL, 0, 0);
	input_set_abs_params(input, ABS_PRESSURE, 0, 0xff, 0, 0);

	touchscreen_parse_properties(input, false, &eeti->props);

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->open = eeti_ts_open;
	input->close = eeti_ts_close;

	eeti->client = client;
	eeti->input = input;

	eeti->attn_gpio = devm_gpiod_get_optional(dev, "attn", GPIOD_IN);
	if (IS_ERR(eeti->attn_gpio))
		return PTR_ERR(eeti->attn_gpio);

	i2c_set_clientdata(client, eeti);
	input_set_drvdata(input, eeti);

	error = devm_request_threaded_irq(dev, client->irq,
					  NULL, eeti_ts_isr,
					  IRQF_ONESHOT,
					  client->name, eeti);
	if (error) {
		dev_err(dev, "Unable to request touchscreen IRQ: %d\n",
			error);
		return error;
	}

	/*
	 * Disable the device for now. It will be enabled once the
	 * input device is opened.
	 */
	eeti_ts_stop(eeti);

	error = input_register_device(input);
	if (error)
		return error;

	return 0;
}