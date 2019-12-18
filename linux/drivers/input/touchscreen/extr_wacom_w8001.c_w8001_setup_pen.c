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
struct w8001_coord {scalar_t__ tilt_y; scalar_t__ tilt_x; scalar_t__ pen_pressure; scalar_t__ y; scalar_t__ x; } ;
struct w8001 {int id; scalar_t__ max_pen_y; scalar_t__ max_pen_x; int /*<<< orphan*/  response; struct input_dev* pen_dev; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  W8001_CMD_QUERY ; 
 int /*<<< orphan*/  W8001_PEN_RESOLUTION ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_pen_data (int /*<<< orphan*/ ,struct w8001_coord*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int w8001_command (struct w8001*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w8001_setup_pen(struct w8001 *w8001, char *basename,
			   size_t basename_sz)
{
	struct input_dev *dev = w8001->pen_dev;
	struct w8001_coord coord;
	int error;

	/* penabled? */
	error = w8001_command(w8001, W8001_CMD_QUERY, true);
	if (error)
		return error;

	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_PEN, dev->keybit);
	__set_bit(BTN_TOOL_RUBBER, dev->keybit);
	__set_bit(BTN_STYLUS, dev->keybit);
	__set_bit(BTN_STYLUS2, dev->keybit);
	__set_bit(INPUT_PROP_DIRECT, dev->propbit);

	parse_pen_data(w8001->response, &coord);
	w8001->max_pen_x = coord.x;
	w8001->max_pen_y = coord.y;

	input_set_abs_params(dev, ABS_X, 0, coord.x, 0, 0);
	input_set_abs_params(dev, ABS_Y, 0, coord.y, 0, 0);
	input_abs_set_res(dev, ABS_X, W8001_PEN_RESOLUTION);
	input_abs_set_res(dev, ABS_Y, W8001_PEN_RESOLUTION);
	input_set_abs_params(dev, ABS_PRESSURE, 0, coord.pen_pressure, 0, 0);
	if (coord.tilt_x && coord.tilt_y) {
		input_set_abs_params(dev, ABS_TILT_X, 0, coord.tilt_x, 0, 0);
		input_set_abs_params(dev, ABS_TILT_Y, 0, coord.tilt_y, 0, 0);
	}

	w8001->id = 0x90;
	strlcat(basename, " Penabled", basename_sz);

	return 0;
}