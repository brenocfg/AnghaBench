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
struct TYPE_4__ {int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  propbit; int /*<<< orphan*/  evbit; TYPE_2__ id; } ;
struct elan_tp_data {unsigned int max_x; unsigned int max_y; struct input_dev* input; int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; scalar_t__ middle_button; scalar_t__ clickpad; int /*<<< orphan*/  product_id; int /*<<< orphan*/  width_y; int /*<<< orphan*/  width_x; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  ELAN_VENDOR_ID ; 
 int ENOMEM ; 
 unsigned int ETP_FINGER_WIDTH ; 
 int /*<<< orphan*/  ETP_MAX_FINGERS ; 
 unsigned int ETP_MAX_PRESSURE ; 
 int /*<<< orphan*/  EV_ABS ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct elan_tp_data*) ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_setup_input_device(struct elan_tp_data *data)
{
	struct device *dev = &data->client->dev;
	struct input_dev *input;
	unsigned int max_width = max(data->width_x, data->width_y);
	unsigned int min_width = min(data->width_x, data->width_y);
	int error;

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = "Elan Touchpad";
	input->id.bustype = BUS_I2C;
	input->id.vendor = ELAN_VENDOR_ID;
	input->id.product = data->product_id;
	input_set_drvdata(input, data);

	error = input_mt_init_slots(input, ETP_MAX_FINGERS,
				    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(dev, "failed to initialize MT slots: %d\n", error);
		return error;
	}

	__set_bit(EV_ABS, input->evbit);
	__set_bit(INPUT_PROP_POINTER, input->propbit);
	if (data->clickpad) {
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
	} else {
		__set_bit(BTN_RIGHT, input->keybit);
		if (data->middle_button)
			__set_bit(BTN_MIDDLE, input->keybit);
	}
	__set_bit(BTN_LEFT, input->keybit);

	/* Set up ST parameters */
	input_set_abs_params(input, ABS_X, 0, data->max_x, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, data->max_y, 0, 0);
	input_abs_set_res(input, ABS_X, data->x_res);
	input_abs_set_res(input, ABS_Y, data->y_res);
	input_set_abs_params(input, ABS_PRESSURE, 0, ETP_MAX_PRESSURE, 0, 0);
	input_set_abs_params(input, ABS_TOOL_WIDTH, 0, ETP_FINGER_WIDTH, 0, 0);
	input_set_abs_params(input, ABS_DISTANCE, 0, 1, 0, 0);

	/* And MT parameters */
	input_set_abs_params(input, ABS_MT_POSITION_X, 0, data->max_x, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, data->max_y, 0, 0);
	input_abs_set_res(input, ABS_MT_POSITION_X, data->x_res);
	input_abs_set_res(input, ABS_MT_POSITION_Y, data->y_res);
	input_set_abs_params(input, ABS_MT_PRESSURE, 0,
			     ETP_MAX_PRESSURE, 0, 0);
	input_set_abs_params(input, ABS_MT_TOUCH_MAJOR, 0,
			     ETP_FINGER_WIDTH * max_width, 0, 0);
	input_set_abs_params(input, ABS_MT_TOUCH_MINOR, 0,
			     ETP_FINGER_WIDTH * min_width, 0, 0);

	data->input = input;

	return 0;
}