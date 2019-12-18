#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct wm831x_ts {int pen_down; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  pd_data_work; scalar_t__ pressure; int /*<<< orphan*/  data_irq; struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
#define  ABS_PRESSURE 130 
#define  ABS_X 129 
#define  ABS_Y 128 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WM831X_INTERRUPT_STATUS_1 ; 
 int WM831X_TCHDATA_EINT ; 
 int WM831X_TCH_DATA_MASK ; 
 int WM831X_TCH_PD ; 
 int WM831X_TCH_X_ENA ; 
 int WM831X_TCH_Y_ENA ; 
 int WM831X_TCH_Z_ENA ; 
 int /*<<< orphan*/  WM831X_TOUCH_CONTROL_1 ; 
 int /*<<< orphan*/  WM831X_TOUCH_DATA_X ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int wm831x_bulk_read (struct wm831x*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t wm831x_ts_data_irq(int irq, void *irq_data)
{
	struct wm831x_ts *wm831x_ts = irq_data;
	struct wm831x *wm831x = wm831x_ts->wm831x;
	static int data_types[] = { ABS_X, ABS_Y, ABS_PRESSURE };
	u16 data[3];
	int count;
	int i, ret;

	if (wm831x_ts->pressure)
		count = 3;
	else
		count = 2;

	wm831x_set_bits(wm831x, WM831X_INTERRUPT_STATUS_1,
			WM831X_TCHDATA_EINT, WM831X_TCHDATA_EINT);

	ret = wm831x_bulk_read(wm831x, WM831X_TOUCH_DATA_X, count,
			       data);
	if (ret != 0) {
		dev_err(wm831x->dev, "Failed to read touch data: %d\n",
			ret);
		return IRQ_NONE;
	}

	/*
	 * We get a pen down reading on every reading, report pen up if any
	 * individual reading does so.
	 */
	wm831x_ts->pen_down = true;
	for (i = 0; i < count; i++) {
		if (!(data[i] & WM831X_TCH_PD)) {
			wm831x_ts->pen_down = false;
			continue;
		}
		input_report_abs(wm831x_ts->input_dev, data_types[i],
				 data[i] & WM831X_TCH_DATA_MASK);
	}

	if (!wm831x_ts->pen_down) {
		/* Switch from data to pen down */
		dev_dbg(wm831x->dev, "IRQ DATA->PD\n");

		disable_irq_nosync(wm831x_ts->data_irq);

		/* Don't need data any more */
		wm831x_set_bits(wm831x, WM831X_TOUCH_CONTROL_1,
				WM831X_TCH_X_ENA | WM831X_TCH_Y_ENA |
				WM831X_TCH_Z_ENA, 0);

		/* Flush any final samples that arrived while reading */
		wm831x_set_bits(wm831x, WM831X_INTERRUPT_STATUS_1,
				WM831X_TCHDATA_EINT, WM831X_TCHDATA_EINT);

		wm831x_bulk_read(wm831x, WM831X_TOUCH_DATA_X, count, data);

		if (wm831x_ts->pressure)
			input_report_abs(wm831x_ts->input_dev,
					 ABS_PRESSURE, 0);

		input_report_key(wm831x_ts->input_dev, BTN_TOUCH, 0);

		schedule_work(&wm831x_ts->pd_data_work);
	} else {
		input_report_key(wm831x_ts->input_dev, BTN_TOUCH, 1);
	}

	input_sync(wm831x_ts->input_dev);

	return IRQ_HANDLED;
}