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
struct input_dev {TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct icn8505_data {int /*<<< orphan*/  prop; struct input_dev* input; struct i2c_client* client; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; struct device dev; } ;
typedef  int /*<<< orphan*/  resolution ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICN8505_MAX_TOUCHES ; 
 int /*<<< orphan*/  ICN8505_REG_CONFIGDATA ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_LEFTMETA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct icn8505_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct icn8505_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct icn8505_data*) ; 
 int /*<<< orphan*/  icn8505_irq ; 
 int icn8505_probe_acpi (struct icn8505_data*,struct device*) ; 
 int icn8505_read_data (struct icn8505_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int icn8505_upload_fw (struct icn8505_data*) ; 
 int /*<<< orphan*/  input_abs_get_max (struct input_dev*,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct icn8505_data*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int icn8505_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct icn8505_data *icn8505;
	struct input_dev *input;
	__le16 resolution[2];
	int error;

	if (!client->irq) {
		dev_err(dev, "No irq specified\n");
		return -EINVAL;
	}

	icn8505 = devm_kzalloc(dev, sizeof(*icn8505), GFP_KERNEL);
	if (!icn8505)
		return -ENOMEM;

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = client->name;
	input->id.bustype = BUS_I2C;

	input_set_capability(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input, EV_ABS, ABS_MT_POSITION_Y);
	input_set_capability(input, EV_KEY, KEY_LEFTMETA);

	icn8505->client = client;
	icn8505->input = input;
	input_set_drvdata(input, icn8505);

	error = icn8505_probe_acpi(icn8505, dev);
	if (error)
		return error;

	error = icn8505_upload_fw(icn8505);
	if (error)
		return error;

	error = icn8505_read_data(icn8505, ICN8505_REG_CONFIGDATA,
				resolution, sizeof(resolution));
	if (error) {
		dev_err(dev, "Error reading resolution: %d\n", error);
		return error;
	}

	input_set_abs_params(input, ABS_MT_POSITION_X, 0,
			     le16_to_cpu(resolution[0]) - 1, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0,
			     le16_to_cpu(resolution[1]) - 1, 0, 0);

	touchscreen_parse_properties(input, true, &icn8505->prop);
	if (!input_abs_get_max(input, ABS_MT_POSITION_X) ||
	    !input_abs_get_max(input, ABS_MT_POSITION_Y)) {
		dev_err(dev, "Error touchscreen-size-x and/or -y missing\n");
		return -EINVAL;
	}

	error = input_mt_init_slots(input, ICN8505_MAX_TOUCHES,
				  INPUT_MT_DIRECT | INPUT_MT_DROP_UNUSED);
	if (error)
		return error;

	error = devm_request_threaded_irq(dev, client->irq, NULL, icn8505_irq,
					IRQF_ONESHOT, client->name, icn8505);
	if (error) {
		dev_err(dev, "Error requesting irq: %d\n", error);
		return error;
	}

	error = input_register_device(input);
	if (error)
		return error;

	i2c_set_clientdata(client, icn8505);
	return 0;
}