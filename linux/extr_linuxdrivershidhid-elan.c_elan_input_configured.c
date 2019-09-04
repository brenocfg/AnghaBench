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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  uniq; int /*<<< orphan*/  phys; } ;
struct hid_input {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bus; int /*<<< orphan*/  uniq; int /*<<< orphan*/  phys; } ;
struct elan_drvdata {struct input_dev* input; int /*<<< orphan*/  res_y; int /*<<< orphan*/  res_x; int /*<<< orphan*/  max_y; int /*<<< orphan*/  max_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  ELAN_MAX_FINGERS ; 
 int /*<<< orphan*/  ELAN_MAX_PRESSURE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INPUT_MT_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int elan_get_device_params (struct hid_device*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct elan_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_not_elan_touchpad (struct hid_device*) ; 

__attribute__((used)) static int elan_input_configured(struct hid_device *hdev, struct hid_input *hi)
{
	int ret;
	struct input_dev *input;
	struct elan_drvdata *drvdata = hid_get_drvdata(hdev);

	if (is_not_elan_touchpad(hdev))
		return 0;

	ret = elan_get_device_params(hdev);
	if (ret)
		return ret;

	input = devm_input_allocate_device(&hdev->dev);
	if (!input)
		return -ENOMEM;

	input->name = "Elan Touchpad";
	input->phys = hdev->phys;
	input->uniq = hdev->uniq;
	input->id.bustype = hdev->bus;
	input->id.vendor  = hdev->vendor;
	input->id.product = hdev->product;
	input->id.version = hdev->version;
	input->dev.parent = &hdev->dev;

	input_set_abs_params(input, ABS_MT_POSITION_X, 0, drvdata->max_x,
			     0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, drvdata->max_y,
			     0, 0);
	input_set_abs_params(input, ABS_MT_PRESSURE, 0, ELAN_MAX_PRESSURE,
			     0, 0);

	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	ret = input_mt_init_slots(input, ELAN_MAX_FINGERS, INPUT_MT_POINTER);
	if (ret) {
		hid_err(hdev, "Failed to init elan MT slots: %d\n", ret);
		return ret;
	}

	input_abs_set_res(input, ABS_X, drvdata->res_x);
	input_abs_set_res(input, ABS_Y, drvdata->res_y);

	ret = input_register_device(input);
	if (ret) {
		hid_err(hdev, "Failed to register elan input device: %d\n",
			ret);
		input_free_device(input);
		return ret;
	}

	drvdata->input = input;

	return 0;
}