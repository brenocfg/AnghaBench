#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_4__ {int version; scalar_t__ product; int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct cyapa {int physical_size_x; int physical_size_y; int max_abs_x; int max_abs_y; int max_z; scalar_t__ gen; int btn_capability; struct input_dev* input; TYPE_3__* client; int /*<<< orphan*/  phys; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_WIDTH_MINOR ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int CAPABILITY_LEFT_BTN_MASK ; 
 int CAPABILITY_MIDDLE_BTN_MASK ; 
 int CAPABILITY_RIGHT_BTN_MASK ; 
 scalar_t__ CYAPA_GEN3 ; 
 scalar_t__ CYAPA_GEN5 ; 
 int /*<<< orphan*/  CYAPA_MAX_MT_SLOTS ; 
 int /*<<< orphan*/  CYAPA_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyapa_close ; 
 int /*<<< orphan*/  cyapa_open ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct cyapa*) ; 

__attribute__((used)) static int cyapa_create_input_dev(struct cyapa *cyapa)
{
	struct device *dev = &cyapa->client->dev;
	struct input_dev *input;
	int error;

	if (!cyapa->physical_size_x || !cyapa->physical_size_y)
		return -EINVAL;

	input = devm_input_allocate_device(dev);
	if (!input) {
		dev_err(dev, "failed to allocate memory for input device.\n");
		return -ENOMEM;
	}

	input->name = CYAPA_NAME;
	input->phys = cyapa->phys;
	input->id.bustype = BUS_I2C;
	input->id.version = 1;
	input->id.product = 0;  /* Means any product in eventcomm. */
	input->dev.parent = &cyapa->client->dev;

	input->open = cyapa_open;
	input->close = cyapa_close;

	input_set_drvdata(input, cyapa);

	__set_bit(EV_ABS, input->evbit);

	/* Finger position */
	input_set_abs_params(input, ABS_MT_POSITION_X, 0, cyapa->max_abs_x, 0,
			     0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, cyapa->max_abs_y, 0,
			     0);
	input_set_abs_params(input, ABS_MT_PRESSURE, 0, cyapa->max_z, 0, 0);
	if (cyapa->gen > CYAPA_GEN3) {
		input_set_abs_params(input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
		input_set_abs_params(input, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
		/*
		 * Orientation is the angle between the vertical axis and
		 * the major axis of the contact ellipse.
		 * The range is -127 to 127.
		 * the positive direction is clockwise form the vertical axis.
		 * If the ellipse of contact degenerates into a circle,
		 * orientation is reported as 0.
		 *
		 * Also, for Gen5 trackpad the accurate of this orientation
		 * value is value + (-30 ~ 30).
		 */
		input_set_abs_params(input, ABS_MT_ORIENTATION,
				-127, 127, 0, 0);
	}
	if (cyapa->gen >= CYAPA_GEN5) {
		input_set_abs_params(input, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);
		input_set_abs_params(input, ABS_MT_WIDTH_MINOR, 0, 255, 0, 0);
		input_set_abs_params(input, ABS_DISTANCE, 0, 1, 0, 0);
	}

	input_abs_set_res(input, ABS_MT_POSITION_X,
			  cyapa->max_abs_x / cyapa->physical_size_x);
	input_abs_set_res(input, ABS_MT_POSITION_Y,
			  cyapa->max_abs_y / cyapa->physical_size_y);

	if (cyapa->btn_capability & CAPABILITY_LEFT_BTN_MASK)
		__set_bit(BTN_LEFT, input->keybit);
	if (cyapa->btn_capability & CAPABILITY_MIDDLE_BTN_MASK)
		__set_bit(BTN_MIDDLE, input->keybit);
	if (cyapa->btn_capability & CAPABILITY_RIGHT_BTN_MASK)
		__set_bit(BTN_RIGHT, input->keybit);

	if (cyapa->btn_capability == CAPABILITY_LEFT_BTN_MASK)
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	/* Handle pointer emulation and unused slots in core */
	error = input_mt_init_slots(input, CYAPA_MAX_MT_SLOTS,
				    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(dev, "failed to initialize MT slots: %d\n", error);
		return error;
	}

	/* Register the device in input subsystem */
	error = input_register_device(input);
	if (error) {
		dev_err(dev, "failed to register input device: %d\n", error);
		return error;
	}

	cyapa->input = input;
	return 0;
}