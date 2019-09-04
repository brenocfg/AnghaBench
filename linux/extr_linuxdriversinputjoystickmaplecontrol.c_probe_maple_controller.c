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
struct maple_driver {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * function_data; } ;
struct maple_device {struct maple_driver* driver; int /*<<< orphan*/  product_name; int /*<<< orphan*/  dev; TYPE_1__ devinfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; struct dc_pad* platform_data; } ;
struct input_dev {TYPE_3__ id; int /*<<< orphan*/  name; TYPE_2__ dev; int /*<<< orphan*/ * evbit; scalar_t__* absbit; scalar_t__* keybit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct dc_pad {struct maple_device* mdev; struct input_dev* dev; } ;

/* Variables and functions */
#define  ABS_BRAKE 145 
#define  ABS_GAS 144 
#define  ABS_HAT0X 143 
#define  ABS_HAT0Y 142 
#define  ABS_HAT1X 141 
#define  ABS_HAT1Y 140 
 int ABS_HAT3Y ; 
#define  ABS_RX 139 
#define  ABS_RY 138 
#define  ABS_X 137 
#define  ABS_Y 136 
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
#define  BTN_A 135 
#define  BTN_B 134 
#define  BTN_C 133 
 int /*<<< orphan*/  BTN_JOYSTICK ; 
#define  BTN_SELECT 132 
#define  BTN_START 131 
#define  BTN_X 130 
#define  BTN_Y 129 
#define  BTN_Z 128 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __set_bit (short const,scalar_t__*) ; 
 unsigned long be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_pad_close ; 
 int /*<<< orphan*/  dc_pad_open ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dc_pad*) ; 
 struct dc_pad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_set_drvdata (struct maple_device*,struct dc_pad*) ; 
 struct maple_device* to_maple_dev (struct device*) ; 
 struct maple_driver* to_maple_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_maple_controller(struct device *dev)
{
	static const short btn_bit[32] = {
		BTN_C, BTN_B, BTN_A, BTN_START, -1, -1, -1, -1,
		BTN_Z, BTN_Y, BTN_X, BTN_SELECT, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
	};

	static const short abs_bit[32] = {
		-1, -1, -1, -1, ABS_HAT0Y, ABS_HAT0Y, ABS_HAT0X, ABS_HAT0X,
		-1, -1, -1, -1, ABS_HAT1Y, ABS_HAT1Y, ABS_HAT1X, ABS_HAT1X,
		ABS_GAS, ABS_BRAKE, ABS_X, ABS_Y, ABS_RX, ABS_RY, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
	};

	struct maple_device *mdev = to_maple_dev(dev);
	struct maple_driver *mdrv = to_maple_driver(dev->driver);
	int i, error;
	struct dc_pad *pad;
	struct input_dev *idev;
	unsigned long data = be32_to_cpu(mdev->devinfo.function_data[0]);

	pad = kzalloc(sizeof(struct dc_pad), GFP_KERNEL);
	idev = input_allocate_device();
	if (!pad || !idev) {
		error = -ENOMEM;
		goto fail;
	}

	pad->dev = idev;
	pad->mdev = mdev;

	idev->open = dc_pad_open;
	idev->close = dc_pad_close;

	for (i = 0; i < 32; i++) {
		if (data & (1 << i)) {
			if (btn_bit[i] >= 0)
				__set_bit(btn_bit[i], idev->keybit);
			else if (abs_bit[i] >= 0)
				__set_bit(abs_bit[i], idev->absbit);
		}
	}

	if (idev->keybit[BIT_WORD(BTN_JOYSTICK)])
		idev->evbit[0] |= BIT_MASK(EV_KEY);

	if (idev->absbit[0])
		idev->evbit[0] |= BIT_MASK(EV_ABS);

	for (i = ABS_X; i <= ABS_BRAKE; i++)
		input_set_abs_params(idev, i, 0, 255, 0, 0);

	for (i = ABS_HAT0X; i <= ABS_HAT3Y; i++)
		input_set_abs_params(idev, i, 1, -1, 0, 0);

	idev->dev.platform_data = pad;
	idev->dev.parent = &mdev->dev;
	idev->name = mdev->product_name;
	idev->id.bustype = BUS_HOST;

	error = input_register_device(idev);
	if (error)
		goto fail;

	mdev->driver = mdrv;
	maple_set_drvdata(mdev, pad);

	return 0;

fail:
	input_free_device(idev);
	kfree(pad);
	maple_set_drvdata(mdev, NULL);
	return error;
}