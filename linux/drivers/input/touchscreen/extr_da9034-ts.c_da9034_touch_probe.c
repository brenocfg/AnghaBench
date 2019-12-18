#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  absbit; TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  name; } ;
struct da9034_touch_pdata {int interval_ms; int /*<<< orphan*/  y_inverted; int /*<<< orphan*/  x_inverted; } ;
struct TYPE_7__ {int /*<<< orphan*/  notifier_call; } ;
struct da9034_touch {int interval_ms; struct input_dev* input_dev; TYPE_1__ notifier; int /*<<< orphan*/  tsi_work; int /*<<< orphan*/  y_inverted; int /*<<< orphan*/  x_inverted; int /*<<< orphan*/  da9034_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9034_touch_close ; 
 int /*<<< orphan*/  da9034_touch_notifier ; 
 int /*<<< orphan*/  da9034_touch_open ; 
 int /*<<< orphan*/  da9034_tsi_work ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct da9034_touch_pdata* dev_get_platdata (TYPE_3__*) ; 
 struct input_dev* devm_input_allocate_device (TYPE_3__*) ; 
 struct da9034_touch* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct da9034_touch*) ; 

__attribute__((used)) static int da9034_touch_probe(struct platform_device *pdev)
{
	struct da9034_touch_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct da9034_touch *touch;
	struct input_dev *input_dev;
	int error;

	touch = devm_kzalloc(&pdev->dev, sizeof(struct da9034_touch),
			     GFP_KERNEL);
	if (!touch) {
		dev_err(&pdev->dev, "failed to allocate driver data\n");
		return -ENOMEM;
	}

	touch->da9034_dev = pdev->dev.parent;

	if (pdata) {
		touch->interval_ms	= pdata->interval_ms;
		touch->x_inverted	= pdata->x_inverted;
		touch->y_inverted	= pdata->y_inverted;
	} else {
		/* fallback into default */
		touch->interval_ms	= 10;
	}

	INIT_DELAYED_WORK(&touch->tsi_work, da9034_tsi_work);
	touch->notifier.notifier_call = da9034_touch_notifier;

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	input_dev->name		= pdev->name;
	input_dev->open		= da9034_touch_open;
	input_dev->close	= da9034_touch_close;
	input_dev->dev.parent	= &pdev->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(ABS_X, input_dev->absbit);
	__set_bit(ABS_Y, input_dev->absbit);
	input_set_abs_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 1023, 0, 0);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	touch->input_dev = input_dev;
	input_set_drvdata(input_dev, touch);

	error = input_register_device(input_dev);
	if (error)
		return error;

	return 0;
}