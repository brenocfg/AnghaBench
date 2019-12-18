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
struct w8001_touch_query {int sensor_id; int /*<<< orphan*/  panel_res; scalar_t__ y; scalar_t__ x; } ;
struct w8001 {int id; scalar_t__ max_pen_y; scalar_t__ max_pen_x; TYPE_1__* serio; int /*<<< orphan*/  pktlen; scalar_t__ max_touch_y; scalar_t__ max_touch_x; int /*<<< orphan*/ * response; struct input_dev* touch_dev; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  propbit; int /*<<< orphan*/  evbit; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOOL_TYPE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 scalar_t__ MT_TOOL_MAX ; 
 int /*<<< orphan*/  W8001_CMD_TOUCHQUERY ; 
 int /*<<< orphan*/  W8001_PEN_RESOLUTION ; 
 int /*<<< orphan*/  W8001_PKTLEN_TOUCH2FG ; 
 int /*<<< orphan*/  W8001_PKTLEN_TOUCH93 ; 
 int /*<<< orphan*/  W8001_PKTLEN_TOUCH9A ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (struct input_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_touchquery (int /*<<< orphan*/ *,struct w8001_touch_query*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int w8001_command (struct w8001*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w8001_setup_touch(struct w8001 *w8001, char *basename,
			     size_t basename_sz)
{
	struct input_dev *dev = w8001->touch_dev;
	struct w8001_touch_query touch;
	int error;


	/* Touch enabled? */
	error = w8001_command(w8001, W8001_CMD_TOUCHQUERY, true);
	if (error)
		return error;
	/*
	 * Some non-touch devices may reply to the touch query. But their
	 * second byte is empty, which indicates touch is not supported.
	 */
	if (!w8001->response[1])
		return -ENXIO;

	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(INPUT_PROP_DIRECT, dev->propbit);

	parse_touchquery(w8001->response, &touch);
	w8001->max_touch_x = touch.x;
	w8001->max_touch_y = touch.y;

	if (w8001->max_pen_x && w8001->max_pen_y) {
		/* if pen is supported scale to pen maximum */
		touch.x = w8001->max_pen_x;
		touch.y = w8001->max_pen_y;
		touch.panel_res = W8001_PEN_RESOLUTION;
	}

	input_set_abs_params(dev, ABS_X, 0, touch.x, 0, 0);
	input_set_abs_params(dev, ABS_Y, 0, touch.y, 0, 0);
	input_abs_set_res(dev, ABS_X, touch.panel_res);
	input_abs_set_res(dev, ABS_Y, touch.panel_res);

	switch (touch.sensor_id) {
	case 0:
	case 2:
		w8001->pktlen = W8001_PKTLEN_TOUCH93;
		w8001->id = 0x93;
		strlcat(basename, " 1FG", basename_sz);
		break;

	case 1:
	case 3:
	case 4:
		w8001->pktlen = W8001_PKTLEN_TOUCH9A;
		strlcat(basename, " 1FG", basename_sz);
		w8001->id = 0x9a;
		break;

	case 5:
		w8001->pktlen = W8001_PKTLEN_TOUCH2FG;

		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		error = input_mt_init_slots(dev, 2, 0);
		if (error) {
			dev_err(&w8001->serio->dev,
				"failed to initialize MT slots: %d\n", error);
			return error;
		}

		input_set_abs_params(dev, ABS_MT_POSITION_X,
					0, touch.x, 0, 0);
		input_set_abs_params(dev, ABS_MT_POSITION_Y,
					0, touch.y, 0, 0);
		input_set_abs_params(dev, ABS_MT_TOOL_TYPE,
					0, MT_TOOL_MAX, 0, 0);
		input_abs_set_res(dev, ABS_MT_POSITION_X, touch.panel_res);
		input_abs_set_res(dev, ABS_MT_POSITION_Y, touch.panel_res);

		strlcat(basename, " 2FG", basename_sz);
		if (w8001->max_pen_x && w8001->max_pen_y)
			w8001->id = 0xE3;
		else
			w8001->id = 0xE2;
		break;
	}

	strlcat(basename, " Touchscreen", basename_sz);

	return 0;
}