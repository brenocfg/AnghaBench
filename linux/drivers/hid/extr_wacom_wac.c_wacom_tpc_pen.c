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
struct wacom_wac {unsigned char* data; int /*<<< orphan*/ * tool; TYPE_1__* shared; struct input_dev* pen_input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int stylus_in_proximity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  delay_pen_events (struct wacom_wac*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 unsigned char le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wacom_tpc_pen(struct wacom_wac *wacom)
{
	unsigned char *data = wacom->data;
	struct input_dev *input = wacom->pen_input;
	bool prox = data[1] & 0x20;

	if (!wacom->shared->stylus_in_proximity) /* first in prox */
		/* Going into proximity select tool */
		wacom->tool[0] = (data[1] & 0x0c) ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;

	/* keep pen state for touch events */
	wacom->shared->stylus_in_proximity = prox;

	/* send pen events only when touch is up or forced out
	 * or touch arbitration is off
	 */
	if (!delay_pen_events(wacom)) {
		input_report_key(input, BTN_STYLUS, data[1] & 0x02);
		input_report_key(input, BTN_STYLUS2, data[1] & 0x10);
		input_report_abs(input, ABS_X, le16_to_cpup((__le16 *)&data[2]));
		input_report_abs(input, ABS_Y, le16_to_cpup((__le16 *)&data[4]));
		input_report_abs(input, ABS_PRESSURE, ((data[7] & 0x07) << 8) | data[6]);
		input_report_key(input, BTN_TOUCH, data[1] & 0x05);
		input_report_key(input, wacom->tool[0], prox);
		return 1;
	}

	return 0;
}