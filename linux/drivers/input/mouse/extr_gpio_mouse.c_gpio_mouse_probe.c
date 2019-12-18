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
struct device {int dummy; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct input_polled_dev {int poll_interval; struct input_dev* input; int /*<<< orphan*/  poll; struct gpio_mouse* private; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct gpio_mouse {int scan_ms; void* bright; void* bmiddle; void* bleft; void* right; void* left; void* down; void* up; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct input_polled_dev* devm_input_allocate_polled_device (struct device*) ; 
 struct gpio_mouse* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_mouse_scan ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct input_polled_dev*) ; 

__attribute__((used)) static int gpio_mouse_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct gpio_mouse *gmouse;
	struct input_polled_dev *input_poll;
	struct input_dev *input;
	int ret;

	gmouse = devm_kzalloc(dev, sizeof(*gmouse), GFP_KERNEL);
	if (!gmouse)
		return -ENOMEM;

	/* Assign some default scanning time */
	ret = device_property_read_u32(dev, "scan-interval-ms",
				       &gmouse->scan_ms);
	if (ret || gmouse->scan_ms == 0) {
		dev_warn(dev, "invalid scan time, set to 50 ms\n");
		gmouse->scan_ms = 50;
	}

	gmouse->up = devm_gpiod_get(dev, "up", GPIOD_IN);
	if (IS_ERR(gmouse->up))
		return PTR_ERR(gmouse->up);
	gmouse->down = devm_gpiod_get(dev, "down", GPIOD_IN);
	if (IS_ERR(gmouse->down))
		return PTR_ERR(gmouse->down);
	gmouse->left = devm_gpiod_get(dev, "left", GPIOD_IN);
	if (IS_ERR(gmouse->left))
		return PTR_ERR(gmouse->left);
	gmouse->right = devm_gpiod_get(dev, "right", GPIOD_IN);
	if (IS_ERR(gmouse->right))
		return PTR_ERR(gmouse->right);

	gmouse->bleft = devm_gpiod_get_optional(dev, "button-left", GPIOD_IN);
	if (IS_ERR(gmouse->bleft))
		return PTR_ERR(gmouse->bleft);
	gmouse->bmiddle = devm_gpiod_get_optional(dev, "button-middle",
						  GPIOD_IN);
	if (IS_ERR(gmouse->bmiddle))
		return PTR_ERR(gmouse->bmiddle);
	gmouse->bright = devm_gpiod_get_optional(dev, "button-right",
						 GPIOD_IN);
	if (IS_ERR(gmouse->bright))
		return PTR_ERR(gmouse->bright);

	input_poll = devm_input_allocate_polled_device(dev);
	if (!input_poll) {
		dev_err(dev, "not enough memory for input device\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, input_poll);

	/* set input-polldev handlers */
	input_poll->private = gmouse;
	input_poll->poll = gpio_mouse_scan;
	input_poll->poll_interval = gmouse->scan_ms;

	input = input_poll->input;
	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &pdev->dev;

	input_set_capability(input, EV_REL, REL_X);
	input_set_capability(input, EV_REL, REL_Y);
	if (gmouse->bleft)
		input_set_capability(input, EV_KEY, BTN_LEFT);
	if (gmouse->bmiddle)
		input_set_capability(input, EV_KEY, BTN_MIDDLE);
	if (gmouse->bright)
		input_set_capability(input, EV_KEY, BTN_RIGHT);

	ret = input_register_polled_device(input_poll);
	if (ret) {
		dev_err(dev, "could not register input device\n");
		return ret;
	}

	dev_dbg(dev, "%d ms scan time, buttons: %s%s%s\n",
		gmouse->scan_ms,
		gmouse->bleft ? "" : "left ",
		gmouse->bmiddle ? "" : "middle ",
		gmouse->bright ? "" : "right");

	return 0;
}