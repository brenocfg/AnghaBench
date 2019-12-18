#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {scalar_t__ vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; } ;
typedef  void* s8 ;
struct TYPE_12__ {TYPE_4__* idev; TYPE_3__* of_dev; int /*<<< orphan*/  bustype; void* zcalib; void* ycalib; void* xcalib; } ;
struct TYPE_11__ {int poll_interval; struct input_dev* input; int /*<<< orphan*/  poll; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  ams_idev_poll ; 
 TYPE_7__ ams_info ; 
 int /*<<< orphan*/  ams_sensors (void**,void**,void**) ; 
 TYPE_4__* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (TYPE_4__*) ; 
 int input_register_polled_device (TYPE_4__*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int joystick ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams_input_enable(void)
{
	struct input_dev *input;
	s8 x, y, z;
	int error;

	ams_sensors(&x, &y, &z);
	ams_info.xcalib = x;
	ams_info.ycalib = y;
	ams_info.zcalib = z;

	ams_info.idev = input_allocate_polled_device();
	if (!ams_info.idev)
		return -ENOMEM;

	ams_info.idev->poll = ams_idev_poll;
	ams_info.idev->poll_interval = 25;

	input = ams_info.idev->input;
	input->name = "Apple Motion Sensor";
	input->id.bustype = ams_info.bustype;
	input->id.vendor = 0;
	input->dev.parent = &ams_info.of_dev->dev;

	input_set_abs_params(input, ABS_X, -50, 50, 3, 0);
	input_set_abs_params(input, ABS_Y, -50, 50, 3, 0);
	input_set_abs_params(input, ABS_Z, -50, 50, 3, 0);

	set_bit(EV_ABS, input->evbit);
	set_bit(EV_KEY, input->evbit);
	set_bit(BTN_TOUCH, input->keybit);

	error = input_register_polled_device(ams_info.idev);
	if (error) {
		input_free_polled_device(ams_info.idev);
		ams_info.idev = NULL;
		return error;
	}

	joystick = true;

	return 0;
}