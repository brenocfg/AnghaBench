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
struct wacom_features {scalar_t__ type; } ;
struct wacom_wac {unsigned char* data; scalar_t__* tool; scalar_t__* id; int /*<<< orphan*/ * serial; struct wacom_features features; struct input_dev* pen_input; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 scalar_t__ BTN_EXTRA ; 
 scalar_t__ BTN_LEFT ; 
 scalar_t__ BTN_MIDDLE ; 
 scalar_t__ BTN_RIGHT ; 
 scalar_t__ BTN_SIDE ; 
 scalar_t__ BTN_STYLUS ; 
 scalar_t__ BTN_STYLUS2 ; 
 scalar_t__ BTN_TOOL_MOUSE ; 
 scalar_t__ BTN_TOUCH ; 
 int /*<<< orphan*/  EV_MSC ; 
 scalar_t__ INTUOS ; 
 scalar_t__ INTUOS3S ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_exit_report(struct wacom_wac *wacom)
{
	struct input_dev *input = wacom->pen_input;
	struct wacom_features *features = &wacom->features;
	unsigned char *data = wacom->data;
	int idx = (features->type == INTUOS) ? (data[1] & 0x01) : 0;

	/*
	 * Reset all states otherwise we lose the initial states
	 * when in-prox next time
	 */
	input_report_abs(input, ABS_X, 0);
	input_report_abs(input, ABS_Y, 0);
	input_report_abs(input, ABS_DISTANCE, 0);
	input_report_abs(input, ABS_TILT_X, 0);
	input_report_abs(input, ABS_TILT_Y, 0);
	if (wacom->tool[idx] >= BTN_TOOL_MOUSE) {
		input_report_key(input, BTN_LEFT, 0);
		input_report_key(input, BTN_MIDDLE, 0);
		input_report_key(input, BTN_RIGHT, 0);
		input_report_key(input, BTN_SIDE, 0);
		input_report_key(input, BTN_EXTRA, 0);
		input_report_abs(input, ABS_THROTTLE, 0);
		input_report_abs(input, ABS_RZ, 0);
	} else {
		input_report_abs(input, ABS_PRESSURE, 0);
		input_report_key(input, BTN_STYLUS, 0);
		input_report_key(input, BTN_STYLUS2, 0);
		input_report_key(input, BTN_TOUCH, 0);
		input_report_abs(input, ABS_WHEEL, 0);
		if (features->type >= INTUOS3S)
			input_report_abs(input, ABS_Z, 0);
	}
	input_report_key(input, wacom->tool[idx], 0);
	input_report_abs(input, ABS_MISC, 0); /* reset tool id */
	input_event(input, EV_MSC, MSC_SERIAL, wacom->serial[idx]);
	wacom->id[idx] = 0;
}