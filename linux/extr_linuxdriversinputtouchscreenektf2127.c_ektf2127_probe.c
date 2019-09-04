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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  (* close ) (struct input_dev*) ;int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; struct device dev; } ;
struct ektf2127_ts {struct input_dev* input; int /*<<< orphan*/  prop; struct i2c_client* client; int /*<<< orphan*/  power_gpios; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int /*<<< orphan*/  EKTF2127_MAX_TOUCHES ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_TRACK ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct ektf2127_ts* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ektf2127_ts*) ; 
 int /*<<< orphan*/  ektf2127_irq ; 
 int ektf2127_query_dimension (struct i2c_client*,int) ; 
 int /*<<< orphan*/  ektf2127_start ; 
 int /*<<< orphan*/  ektf2127_stop (struct input_dev*) ; 
 int /*<<< orphan*/  i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ektf2127_ts*) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct ektf2127_ts*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ektf2127_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ektf2127_ts *ts;
	struct input_dev *input;
	u8 buf[4];
	int max_x, max_y;
	int error;

	if (!client->irq) {
		dev_err(dev, "Error no irq specified\n");
		return -EINVAL;
	}

	ts = devm_kzalloc(dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	/* This requests the gpio *and* turns on the touchscreen controller */
	ts->power_gpios = devm_gpiod_get(dev, "power", GPIOD_OUT_HIGH);
	if (IS_ERR(ts->power_gpios)) {
		error = PTR_ERR(ts->power_gpios);
		if (error != -EPROBE_DEFER)
			dev_err(dev, "Error getting power gpio: %d\n", error);
		return error;
	}

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->open = ektf2127_start;
	input->close = ektf2127_stop;

	ts->client = client;

	/* Read hello (ignore result, depends on initial power state) */
	msleep(20);
	i2c_master_recv(ts->client, buf, sizeof(buf));

	/* Read resolution from chip */
	max_x = ektf2127_query_dimension(client, true);
	if (max_x < 0)
		return max_x;

	max_y = ektf2127_query_dimension(client, false);
	if (max_y < 0)
		return max_y;

	input_set_abs_params(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	touchscreen_parse_properties(input, true, &ts->prop);

	error = input_mt_init_slots(input, EKTF2127_MAX_TOUCHES,
				    INPUT_MT_DIRECT |
					INPUT_MT_DROP_UNUSED |
					INPUT_MT_TRACK);
	if (error)
		return error;

	ts->input = input;
	input_set_drvdata(input, ts);

	error = devm_request_threaded_irq(dev, client->irq,
					  NULL, ektf2127_irq,
					  IRQF_ONESHOT, client->name, ts);
	if (error) {
		dev_err(dev, "Error requesting irq: %d\n", error);
		return error;
	}

	/* Stop device till opened */
	ektf2127_stop(ts->input);

	error = input_register_device(input);
	if (error)
		return error;

	i2c_set_clientdata(client, ts);

	return 0;
}