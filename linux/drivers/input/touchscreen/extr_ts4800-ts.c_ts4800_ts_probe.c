#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ts4800_ts {int /*<<< orphan*/  phys; int /*<<< orphan*/ * dev; struct input_polled_dev* poll_dev; int /*<<< orphan*/  base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct input_polled_dev {TYPE_1__* input; int /*<<< orphan*/  poll; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  poll_interval; struct ts4800_ts* private; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_12BIT ; 
 int /*<<< orphan*/  POLL_INTERVAL ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct input_polled_dev* devm_input_allocate_polled_device (int /*<<< orphan*/ *) ; 
 struct ts4800_ts* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int ts4800_parse_dt (struct platform_device*,struct ts4800_ts*) ; 
 int /*<<< orphan*/  ts4800_ts_close ; 
 int /*<<< orphan*/  ts4800_ts_open ; 
 int /*<<< orphan*/  ts4800_ts_poll ; 

__attribute__((used)) static int ts4800_ts_probe(struct platform_device *pdev)
{
	struct input_polled_dev *poll_dev;
	struct ts4800_ts *ts;
	int error;

	ts = devm_kzalloc(&pdev->dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	error = ts4800_parse_dt(pdev, ts);
	if (error)
		return error;

	ts->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(ts->base))
		return PTR_ERR(ts->base);

	poll_dev = devm_input_allocate_polled_device(&pdev->dev);
	if (!poll_dev)
		return -ENOMEM;

	snprintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(&pdev->dev));
	ts->poll_dev = poll_dev;
	ts->dev = &pdev->dev;

	poll_dev->private = ts;
	poll_dev->poll_interval = POLL_INTERVAL;
	poll_dev->open = ts4800_ts_open;
	poll_dev->close = ts4800_ts_close;
	poll_dev->poll = ts4800_ts_poll;

	poll_dev->input->name = "TS-4800 Touchscreen";
	poll_dev->input->phys = ts->phys;

	input_set_capability(poll_dev->input, EV_KEY, BTN_TOUCH);
	input_set_abs_params(poll_dev->input, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_abs_params(poll_dev->input, ABS_Y, 0, MAX_12BIT, 0, 0);

	error = input_register_polled_device(poll_dev);
	if (error) {
		dev_err(&pdev->dev,
			"Unabled to register polled input device (%d)\n",
			error);
		return error;
	}

	return 0;
}