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
struct input_dev {char* name; TYPE_1__ id; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct exc3000_data {int /*<<< orphan*/  prop; struct input_dev* input; int /*<<< orphan*/  timer; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXC3000_NUM_SLOTS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INPUT_MT_DIRECT ; 
 int INPUT_MT_DROP_UNUSED ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct exc3000_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct exc3000_data*) ; 
 int /*<<< orphan*/  exc3000_interrupt ; 
 int /*<<< orphan*/  exc3000_timer ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (struct input_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exc3000_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct exc3000_data *data;
	struct input_dev *input;
	int error;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	timer_setup(&data->timer, exc3000_timer, 0);

	input = devm_input_allocate_device(&client->dev);
	if (!input)
		return -ENOMEM;

	data->input = input;

	input->name = "EETI EXC3000 Touch Screen";
	input->id.bustype = BUS_I2C;

	input_set_abs_params(input, ABS_MT_POSITION_X, 0, 4095, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, 4095, 0, 0);
	touchscreen_parse_properties(input, true, &data->prop);

	error = input_mt_init_slots(input, EXC3000_NUM_SLOTS,
				    INPUT_MT_DIRECT | INPUT_MT_DROP_UNUSED);
	if (error)
		return error;

	error = input_register_device(input);
	if (error)
		return error;

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, exc3000_interrupt, IRQF_ONESHOT,
					  client->name, data);
	if (error)
		return error;

	return 0;
}