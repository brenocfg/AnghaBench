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
struct w8001_coord {int /*<<< orphan*/  rdy; int /*<<< orphan*/  f1; int /*<<< orphan*/  tsw; int /*<<< orphan*/  pen_pressure; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  f2; } ;
struct w8001 {int type; struct input_dev* pen_dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int const BTN_STYLUS ; 
 int const BTN_STYLUS2 ; 
#define  BTN_TOOL_FINGER 130 
 int const BTN_TOOL_PEN ; 
#define  BTN_TOOL_RUBBER 129 
 int const BTN_TOUCH ; 
#define  KEY_RESERVED 128 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void report_pen_events(struct w8001 *w8001, struct w8001_coord *coord)
{
	struct input_dev *dev = w8001->pen_dev;

	/*
	 * We have 1 bit for proximity (rdy) and 3 bits for tip, side,
	 * side2/eraser. If rdy && f2 are set, this can be either pen + side2,
	 * or eraser. Assume:
	 * - if dev is already in proximity and f2 is toggled → pen + side2
	 * - if dev comes into proximity with f2 set → eraser
	 * If f2 disappears after assuming eraser, fake proximity out for
	 * eraser and in for pen.
	 */

	switch (w8001->type) {
	case BTN_TOOL_RUBBER:
		if (!coord->f2) {
			input_report_abs(dev, ABS_PRESSURE, 0);
			input_report_key(dev, BTN_TOUCH, 0);
			input_report_key(dev, BTN_STYLUS, 0);
			input_report_key(dev, BTN_STYLUS2, 0);
			input_report_key(dev, BTN_TOOL_RUBBER, 0);
			input_sync(dev);
			w8001->type = BTN_TOOL_PEN;
		}
		break;

	case BTN_TOOL_FINGER:
	case KEY_RESERVED:
		w8001->type = coord->f2 ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;
		break;

	default:
		input_report_key(dev, BTN_STYLUS2, coord->f2);
		break;
	}

	input_report_abs(dev, ABS_X, coord->x);
	input_report_abs(dev, ABS_Y, coord->y);
	input_report_abs(dev, ABS_PRESSURE, coord->pen_pressure);
	input_report_key(dev, BTN_TOUCH, coord->tsw);
	input_report_key(dev, BTN_STYLUS, coord->f1);
	input_report_key(dev, w8001->type, coord->rdy);
	input_sync(dev);

	if (!coord->rdy)
		w8001->type = KEY_RESERVED;
}