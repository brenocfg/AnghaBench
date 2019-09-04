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
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct at91_adc_state {scalar_t__ touchscreen_type; struct input_dev* ts_input; TYPE_3__* caps; } ;
struct TYPE_6__ {scalar_t__ has_tsmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 scalar_t__ ATMEL_ADC_TOUCHSCREEN_4WIRE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int MAX_POS_BITS ; 
 int MAX_RLPOS_BITS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_ts_close ; 
 int /*<<< orphan*/  atmel_ts_open ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* iio_priv_to_dev (struct at91_adc_state*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct at91_adc_state*) ; 

__attribute__((used)) static int at91_ts_register(struct at91_adc_state *st,
		struct platform_device *pdev)
{
	struct input_dev *input;
	struct iio_dev *idev = iio_priv_to_dev(st);
	int ret;

	input = input_allocate_device();
	if (!input) {
		dev_err(&idev->dev, "Failed to allocate TS device!\n");
		return -ENOMEM;
	}

	input->name = DRIVER_NAME;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &pdev->dev;
	input->open = atmel_ts_open;
	input->close = atmel_ts_close;

	__set_bit(EV_ABS, input->evbit);
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_TOUCH, input->keybit);
	if (st->caps->has_tsmr) {
		input_set_abs_params(input, ABS_X, 0, (1 << MAX_POS_BITS) - 1,
				     0, 0);
		input_set_abs_params(input, ABS_Y, 0, (1 << MAX_POS_BITS) - 1,
				     0, 0);
		input_set_abs_params(input, ABS_PRESSURE, 0, 0xffffff, 0, 0);
	} else {
		if (st->touchscreen_type != ATMEL_ADC_TOUCHSCREEN_4WIRE) {
			dev_err(&pdev->dev,
				"This touchscreen controller only support 4 wires\n");
			ret = -EINVAL;
			goto err;
		}

		input_set_abs_params(input, ABS_X, 0, (1 << MAX_RLPOS_BITS) - 1,
				     0, 0);
		input_set_abs_params(input, ABS_Y, 0, (1 << MAX_RLPOS_BITS) - 1,
				     0, 0);
	}

	st->ts_input = input;
	input_set_drvdata(input, st);

	ret = input_register_device(input);
	if (ret)
		goto err;

	return ret;

err:
	input_free_device(st->ts_input);
	return ret;
}