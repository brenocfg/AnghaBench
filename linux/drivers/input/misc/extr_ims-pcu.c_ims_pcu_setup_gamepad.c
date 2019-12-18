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
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct ims_pcu_gamepad {int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct input_dev* input; } ;
struct ims_pcu {int device_no; struct ims_pcu_gamepad* gamepad; int /*<<< orphan*/  dev; TYPE_2__* ctrl_intf; int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ims_pcu_gamepad*) ; 
 struct ims_pcu_gamepad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ims_pcu_setup_gamepad(struct ims_pcu *pcu)
{
	struct ims_pcu_gamepad *gamepad;
	struct input_dev *input;
	int error;

	gamepad = kzalloc(sizeof(struct ims_pcu_gamepad), GFP_KERNEL);
	input = input_allocate_device();
	if (!gamepad || !input) {
		dev_err(pcu->dev,
			"Not enough memory for gamepad device\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	gamepad->input = input;

	snprintf(gamepad->name, sizeof(gamepad->name),
		 "IMS PCU#%d Gamepad Interface", pcu->device_no);

	usb_make_path(pcu->udev, gamepad->phys, sizeof(gamepad->phys));
	strlcat(gamepad->phys, "/input1", sizeof(gamepad->phys));

	input->name = gamepad->name;
	input->phys = gamepad->phys;
	usb_to_input_id(pcu->udev, &input->id);
	input->dev.parent = &pcu->ctrl_intf->dev;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_A, input->keybit);
	__set_bit(BTN_B, input->keybit);
	__set_bit(BTN_X, input->keybit);
	__set_bit(BTN_Y, input->keybit);
	__set_bit(BTN_START, input->keybit);
	__set_bit(BTN_SELECT, input->keybit);

	__set_bit(EV_ABS, input->evbit);
	input_set_abs_params(input, ABS_X, -1, 1, 0, 0);
	input_set_abs_params(input, ABS_Y, -1, 1, 0, 0);

	error = input_register_device(input);
	if (error) {
		dev_err(pcu->dev,
			"Failed to register gamepad input device: %d\n",
			error);
		goto err_free_mem;
	}

	pcu->gamepad = gamepad;
	return 0;

err_free_mem:
	input_free_device(input);
	kfree(gamepad);
	return -ENOMEM;
}