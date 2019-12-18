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
struct mcs_platform_data {int /*<<< orphan*/  (* cfg_pin ) () ;} ;
struct mcs5000_ts_data {struct input_dev* input_dev; struct i2c_client* client; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  MCS5000_MAX_XC ; 
 int /*<<< orphan*/  MCS5000_MAX_YC ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mcs_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct mcs5000_ts_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct mcs5000_ts_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mcs5000_ts_data*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs5000_ts_interrupt ; 
 int /*<<< orphan*/  mcs5000_ts_phys_init (struct mcs5000_ts_data*,struct mcs_platform_data const*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int mcs5000_ts_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	const struct mcs_platform_data *pdata;
	struct mcs5000_ts_data *data;
	struct input_dev *input_dev;
	int error;

	pdata = dev_get_platdata(&client->dev);
	if (!pdata)
		return -EINVAL;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		dev_err(&client->dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

	data->client = client;

	input_dev = devm_input_allocate_device(&client->dev);
	if (!input_dev) {
		dev_err(&client->dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	input_dev->name = "MELFAS MCS-5000 Touchscreen";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	input_set_abs_params(input_dev, ABS_X, 0, MCS5000_MAX_XC, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, MCS5000_MAX_YC, 0, 0);

	data->input_dev = input_dev;

	if (pdata->cfg_pin)
		pdata->cfg_pin();

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, mcs5000_ts_interrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "mcs5000_ts", data);
	if (error) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return error;
	}

	error = input_register_device(data->input_dev);
	if (error) {
		dev_err(&client->dev, "Failed to register input device\n");
		return error;
	}

	mcs5000_ts_phys_init(data, pdata);
	i2c_set_clientdata(client, data);

	return 0;
}