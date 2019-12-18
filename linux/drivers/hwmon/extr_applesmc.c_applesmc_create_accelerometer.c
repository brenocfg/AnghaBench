#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/ * evbit; TYPE_2__ dev; TYPE_1__ id; } ;
struct TYPE_13__ {struct input_dev* input; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  has_accelerometer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  APPLESMC_INPUT_FLAT ; 
 int /*<<< orphan*/  APPLESMC_INPUT_FUZZ ; 
 int /*<<< orphan*/  APPLESMC_POLL_INTERVAL ; 
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  accelerometer_group ; 
 int /*<<< orphan*/  applesmc_calibrate () ; 
 int applesmc_create_nodes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  applesmc_destroy_nodes (int /*<<< orphan*/ ) ; 
 TYPE_5__* applesmc_idev ; 
 int /*<<< orphan*/  applesmc_idev_poll ; 
 TYPE_5__* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (TYPE_5__*) ; 
 int input_register_polled_device (TYPE_5__*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* pdev ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_3__ smcreg ; 

__attribute__((used)) static int applesmc_create_accelerometer(void)
{
	struct input_dev *idev;
	int ret;

	if (!smcreg.has_accelerometer)
		return 0;

	ret = applesmc_create_nodes(accelerometer_group, 1);
	if (ret)
		goto out;

	applesmc_idev = input_allocate_polled_device();
	if (!applesmc_idev) {
		ret = -ENOMEM;
		goto out_sysfs;
	}

	applesmc_idev->poll = applesmc_idev_poll;
	applesmc_idev->poll_interval = APPLESMC_POLL_INTERVAL;

	/* initial calibrate for the input device */
	applesmc_calibrate();

	/* initialize the input device */
	idev = applesmc_idev->input;
	idev->name = "applesmc";
	idev->id.bustype = BUS_HOST;
	idev->dev.parent = &pdev->dev;
	idev->evbit[0] = BIT_MASK(EV_ABS);
	input_set_abs_params(idev, ABS_X,
			-256, 256, APPLESMC_INPUT_FUZZ, APPLESMC_INPUT_FLAT);
	input_set_abs_params(idev, ABS_Y,
			-256, 256, APPLESMC_INPUT_FUZZ, APPLESMC_INPUT_FLAT);

	ret = input_register_polled_device(applesmc_idev);
	if (ret)
		goto out_idev;

	return 0;

out_idev:
	input_free_polled_device(applesmc_idev);

out_sysfs:
	applesmc_destroy_nodes(accelerometer_group);

out:
	pr_warn("driver init failed (ret=%d)!\n", ret);
	return ret;
}