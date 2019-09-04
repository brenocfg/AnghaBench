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
struct mxs_lradc_ts {struct input_dev* ts_input; struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  propbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  LRADC_SINGLE_SAMPLE_MASK ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_ts_close ; 
 int /*<<< orphan*/  mxs_lradc_ts_open ; 

__attribute__((used)) static int mxs_lradc_ts_register(struct mxs_lradc_ts *ts)
{
	struct input_dev *input;
	struct device *dev = ts->dev;

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = "mxs-lradc-ts";
	input->id.bustype = BUS_HOST;
	input->open = mxs_lradc_ts_open;
	input->close = mxs_lradc_ts_close;

	__set_bit(INPUT_PROP_DIRECT, input->propbit);
	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_abs_params(input, ABS_X, 0, LRADC_SINGLE_SAMPLE_MASK, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, LRADC_SINGLE_SAMPLE_MASK, 0, 0);
	input_set_abs_params(input, ABS_PRESSURE, 0, LRADC_SINGLE_SAMPLE_MASK,
			     0, 0);

	ts->ts_input = input;
	input_set_drvdata(input, ts);

	return input_register_device(input);
}