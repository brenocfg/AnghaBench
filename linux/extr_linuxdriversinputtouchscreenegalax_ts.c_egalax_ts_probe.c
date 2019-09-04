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
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct egalax_ts {struct input_dev* input_dev; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  EGALAX_MAX_X ; 
 int /*<<< orphan*/  EGALAX_MAX_Y ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  MAX_SUPPORT_POINTS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct egalax_ts* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct egalax_ts*) ; 
 int egalax_firmware_version (struct i2c_client*) ; 
 int /*<<< orphan*/  egalax_ts_interrupt ; 
 int egalax_wake_up_device (struct i2c_client*) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int egalax_ts_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct egalax_ts *ts;
	struct input_dev *input_dev;
	int error;

	ts = devm_kzalloc(&client->dev, sizeof(struct egalax_ts), GFP_KERNEL);
	if (!ts) {
		dev_err(&client->dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

	input_dev = devm_input_allocate_device(&client->dev);
	if (!input_dev) {
		dev_err(&client->dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

	ts->client = client;
	ts->input_dev = input_dev;

	/* controller may be in sleep, wake it up. */
	error = egalax_wake_up_device(client);
	if (error) {
		dev_err(&client->dev, "Failed to wake up the controller\n");
		return error;
	}

	error = egalax_firmware_version(client);
	if (error < 0) {
		dev_err(&client->dev, "Failed to read firmware version\n");
		return error;
	}

	input_dev->name = "EETI eGalax Touch Screen";
	input_dev->id.bustype = BUS_I2C;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_abs_params(input_dev, ABS_X, 0, EGALAX_MAX_X, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, EGALAX_MAX_Y, 0, 0);
	input_set_abs_params(input_dev,
			     ABS_MT_POSITION_X, 0, EGALAX_MAX_X, 0, 0);
	input_set_abs_params(input_dev,
			     ABS_MT_POSITION_Y, 0, EGALAX_MAX_Y, 0, 0);
	input_mt_init_slots(input_dev, MAX_SUPPORT_POINTS, 0);

	error = devm_request_threaded_irq(&client->dev, client->irq, NULL,
					  egalax_ts_interrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "egalax_ts", ts);
	if (error < 0) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return error;
	}

	error = input_register_device(ts->input_dev);
	if (error)
		return error;

	return 0;
}