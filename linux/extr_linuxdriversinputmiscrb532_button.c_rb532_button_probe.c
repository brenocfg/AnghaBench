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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct input_polled_dev {TYPE_3__* input; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {char* name; char* phys; TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  RB532_BTN_KSYM ; 
 int /*<<< orphan*/  RB532_BTN_RATE ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct input_polled_dev*) ; 
 struct input_polled_dev* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (struct input_polled_dev*) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb532_button_poll ; 

__attribute__((used)) static int rb532_button_probe(struct platform_device *pdev)
{
	struct input_polled_dev *poll_dev;
	int error;

	poll_dev = input_allocate_polled_device();
	if (!poll_dev)
		return -ENOMEM;

	poll_dev->poll = rb532_button_poll;
	poll_dev->poll_interval = RB532_BTN_RATE;

	poll_dev->input->name = "rb532 button";
	poll_dev->input->phys = "rb532/button0";
	poll_dev->input->id.bustype = BUS_HOST;
	poll_dev->input->dev.parent = &pdev->dev;

	dev_set_drvdata(&pdev->dev, poll_dev);

	input_set_capability(poll_dev->input, EV_KEY, RB532_BTN_KSYM);

	error = input_register_polled_device(poll_dev);
	if (error) {
		input_free_polled_device(poll_dev);
		return error;
	}

	return 0;
}