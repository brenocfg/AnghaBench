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
struct uclogic_drvdata {struct input_dev* pen_input; } ;
struct timer_list {int dummy; } ;
struct input_dev {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 struct uclogic_drvdata* drvdata ; 
 struct uclogic_drvdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  inrange_timer ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uclogic_inrange_timeout(struct timer_list *t)
{
	struct uclogic_drvdata *drvdata = from_timer(drvdata, t,
							inrange_timer);
	struct input_dev *input = drvdata->pen_input;

	if (input == NULL)
		return;
	input_report_abs(input, ABS_PRESSURE, 0);
	/* If BTN_TOUCH state is changing */
	if (test_bit(BTN_TOUCH, input->key)) {
		input_event(input, EV_MSC, MSC_SCAN,
				/* Digitizer Tip Switch usage */
				0xd0042);
		input_report_key(input, BTN_TOUCH, 0);
	}
	input_report_key(input, BTN_TOOL_PEN, 0);
	input_sync(input);
}