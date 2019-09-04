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
struct rc_dev {char* device_name; int /*<<< orphan*/  input_phys; TYPE_1__* raw; } ;
struct input_dev {int /*<<< orphan*/  mscbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct imon_dec {int stick_keyboard; struct input_dev* idev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct imon_dec imon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct imon_dec*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int ir_imon_register(struct rc_dev *dev)
{
	struct input_dev *idev;
	struct imon_dec *imon = &dev->raw->imon;
	int ret;

	idev = input_allocate_device();
	if (!idev)
		return -ENOMEM;

	snprintf(imon->name, sizeof(imon->name),
		 "iMON PAD Stick (%s)", dev->device_name);
	idev->name = imon->name;
	idev->phys = dev->input_phys;

	/* Mouse bits */
	set_bit(EV_REL, idev->evbit);
	set_bit(EV_KEY, idev->evbit);
	set_bit(REL_X, idev->relbit);
	set_bit(REL_Y, idev->relbit);
	set_bit(BTN_LEFT, idev->keybit);
	set_bit(BTN_RIGHT, idev->keybit);

	/* Report scancodes too */
	set_bit(EV_MSC, idev->evbit);
	set_bit(MSC_SCAN, idev->mscbit);

	input_set_drvdata(idev, imon);

	ret = input_register_device(idev);
	if (ret < 0) {
		input_free_device(idev);
		return -EIO;
	}

	imon->idev = idev;
	imon->stick_keyboard = false;

	return 0;
}