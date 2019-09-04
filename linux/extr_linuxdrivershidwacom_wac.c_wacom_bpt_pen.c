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
struct wacom_features {unsigned char distance_max; } ;
struct wacom_wac {unsigned char* data; int* id; int reporting_data; int /*<<< orphan*/ * tool; TYPE_1__* shared; struct input_dev* pen_input; struct wacom_features features; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int stylus_in_proximity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ERASER_DEVICE_ID ; 
 int STYLUS_DEVICE_ID ; 
 unsigned char WACOM_REPORT_PENABLED ; 
 scalar_t__ delay_pen_events (struct wacom_wac*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wacom_bpt_pen(struct wacom_wac *wacom)
{
	struct wacom_features *features = &wacom->features;
	struct input_dev *input = wacom->pen_input;
	unsigned char *data = wacom->data;
	int x = 0, y = 0, p = 0, d = 0;
	bool pen = false, btn1 = false, btn2 = false;
	bool range, prox, rdy;

	if (data[0] != WACOM_REPORT_PENABLED)
	    return 0;

	range = (data[1] & 0x80) == 0x80;
	prox = (data[1] & 0x40) == 0x40;
	rdy = (data[1] & 0x20) == 0x20;

	wacom->shared->stylus_in_proximity = range;
	if (delay_pen_events(wacom))
		return 0;

	if (rdy) {
		p = le16_to_cpup((__le16 *)&data[6]);
		pen = data[1] & 0x01;
		btn1 = data[1] & 0x02;
		btn2 = data[1] & 0x04;
	}
	if (prox) {
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);

		if (data[1] & 0x08) {
			wacom->tool[0] = BTN_TOOL_RUBBER;
			wacom->id[0] = ERASER_DEVICE_ID;
		} else {
			wacom->tool[0] = BTN_TOOL_PEN;
			wacom->id[0] = STYLUS_DEVICE_ID;
		}
		wacom->reporting_data = true;
	}
	if (range) {
		/*
		 * Convert distance from out prox to distance from tablet.
		 * distance will be greater than distance_max once
		 * touching and applying pressure; do not report negative
		 * distance.
		 */
		if (data[8] <= features->distance_max)
			d = features->distance_max - data[8];
	} else {
		wacom->id[0] = 0;
	}

	if (wacom->reporting_data) {
		input_report_key(input, BTN_TOUCH, pen);
		input_report_key(input, BTN_STYLUS, btn1);
		input_report_key(input, BTN_STYLUS2, btn2);

		if (prox || !range) {
			input_report_abs(input, ABS_X, x);
			input_report_abs(input, ABS_Y, y);
		}
		input_report_abs(input, ABS_PRESSURE, p);
		input_report_abs(input, ABS_DISTANCE, d);

		input_report_key(input, wacom->tool[0], range); /* PEN or RUBBER */
		input_report_abs(input, ABS_MISC, wacom->id[0]); /* TOOL ID */
	}

	if (!range) {
		wacom->reporting_data = false;
	}

	return 1;
}