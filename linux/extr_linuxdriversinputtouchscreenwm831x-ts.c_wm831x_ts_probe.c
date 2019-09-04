#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wm831x_ts {int pressure; void* data_irq; void* pd_irq; int /*<<< orphan*/  pd_data_work; struct input_dev* input_dev; struct wm831x* wm831x; } ;
struct wm831x_touch_pdata {int pressure; int isel; int data_irqf; int pd_irqf; scalar_t__ fivewire; void* pd_irq; void* data_irq; } ;
struct wm831x_pdata {struct wm831x_touch_pdata* touch; } ;
struct wm831x {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {TYPE_2__* parent; } ;
struct input_dev {char* name; char* phys; TYPE_1__ dev; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WM831X_TCH_5WIRE ; 
 int WM831X_TCH_ISEL ; 
 int WM831X_TCH_PDONLY ; 
 int WM831X_TCH_RATE_MASK ; 
 int /*<<< orphan*/  WM831X_TOUCH_CONTROL_1 ; 
 int /*<<< orphan*/  WM831X_TOUCH_CONTROL_2 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,...) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm831x_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (TYPE_2__*) ; 
 struct wm831x_ts* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (void*) ; 
 int /*<<< orphan*/  free_irq (void*,struct wm831x_ts*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct wm831x_ts*) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm831x_ts*) ; 
 int request_threaded_irq (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct wm831x_ts*) ; 
 void* wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_pd_data_work ; 
 int /*<<< orphan*/  wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm831x_ts_data_irq ; 
 int /*<<< orphan*/  wm831x_ts_input_close ; 
 int /*<<< orphan*/  wm831x_ts_input_open ; 
 int /*<<< orphan*/  wm831x_ts_pen_down_irq ; 

__attribute__((used)) static int wm831x_ts_probe(struct platform_device *pdev)
{
	struct wm831x_ts *wm831x_ts;
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *core_pdata = dev_get_platdata(pdev->dev.parent);
	struct wm831x_touch_pdata *pdata = NULL;
	struct input_dev *input_dev;
	int error, irqf;

	if (core_pdata)
		pdata = core_pdata->touch;

	wm831x_ts = devm_kzalloc(&pdev->dev, sizeof(struct wm831x_ts),
				 GFP_KERNEL);
	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!wm831x_ts || !input_dev) {
		error = -ENOMEM;
		goto err_alloc;
	}

	wm831x_ts->wm831x = wm831x;
	wm831x_ts->input_dev = input_dev;
	INIT_WORK(&wm831x_ts->pd_data_work, wm831x_pd_data_work);

	/*
	 * If we have a direct IRQ use it, otherwise use the interrupt
	 * from the WM831x IRQ controller.
	 */
	wm831x_ts->data_irq = wm831x_irq(wm831x,
					 platform_get_irq_byname(pdev,
								 "TCHDATA"));
	if (pdata && pdata->data_irq)
		wm831x_ts->data_irq = pdata->data_irq;

	wm831x_ts->pd_irq = wm831x_irq(wm831x,
				       platform_get_irq_byname(pdev, "TCHPD"));
	if (pdata && pdata->pd_irq)
		wm831x_ts->pd_irq = pdata->pd_irq;

	if (pdata)
		wm831x_ts->pressure = pdata->pressure;
	else
		wm831x_ts->pressure = true;

	/* Five wire touchscreens can't report pressure */
	if (pdata && pdata->fivewire) {
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
				WM831X_TCH_5WIRE, WM831X_TCH_5WIRE);

		/* Pressure measurements are not possible for five wire mode */
		WARN_ON(pdata->pressure && pdata->fivewire);
		wm831x_ts->pressure = false;
	} else {
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
				WM831X_TCH_5WIRE, 0);
	}

	if (pdata) {
		switch (pdata->isel) {
		default:
			dev_err(&pdev->dev, "Unsupported ISEL setting: %d\n",
				pdata->isel);
			/* Fall through */
		case 200:
		case 0:
			wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
					WM831X_TCH_ISEL, 0);
			break;
		case 400:
			wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
					WM831X_TCH_ISEL, WM831X_TCH_ISEL);
			break;
		}
	}

	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_2,
			WM831X_TCH_PDONLY, 0);

	/* Default to 96 samples/sec */
	wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
			WM831X_TCH_RATE_MASK, 6);

	if (pdata && pdata->data_irqf)
		irqf = pdata->data_irqf;
	else
		irqf = IRQF_TRIGGER_HIGH;

	error = request_threaded_irq(wm831x_ts->data_irq,
				     NULL, wm831x_ts_data_irq,
				     irqf | IRQF_ONESHOT,
				     "Touchscreen data", wm831x_ts);
	if (error) {
		dev_err(&pdev->dev, "Failed to request data IRQ %d: %d\n",
			wm831x_ts->data_irq, error);
		goto err_alloc;
	}
	disable_irq(wm831x_ts->data_irq);

	if (pdata && pdata->pd_irqf)
		irqf = pdata->pd_irqf;
	else
		irqf = IRQF_TRIGGER_HIGH;

	error = request_threaded_irq(wm831x_ts->pd_irq,
				     NULL, wm831x_ts_pen_down_irq,
				     irqf | IRQF_ONESHOT,
				     "Touchscreen pen down", wm831x_ts);
	if (error) {
		dev_err(&pdev->dev, "Failed to request pen down IRQ %d: %d\n",
			wm831x_ts->pd_irq, error);
		goto err_data_irq;
	}

	/* set up touch configuration */
	input_dev->name = "WM831x touchscreen";
	input_dev->phys = "wm831x";
	input_dev->open = wm831x_ts_input_open;
	input_dev->close = wm831x_ts_input_close;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_abs_params(input_dev, ABS_X, 0, 4095, 5, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 4095, 5, 0);
	if (wm831x_ts->pressure)
		input_set_abs_params(input_dev, ABS_PRESSURE, 0, 4095, 5, 0);

	input_set_drvdata(input_dev, wm831x_ts);
	input_dev->dev.parent = &pdev->dev;

	error = input_register_device(input_dev);
	if (error)
		goto err_pd_irq;

	platform_set_drvdata(pdev, wm831x_ts);
	return 0;

err_pd_irq:
	free_irq(wm831x_ts->pd_irq, wm831x_ts);
err_data_irq:
	free_irq(wm831x_ts->data_irq, wm831x_ts);
err_alloc:

	return error;
}