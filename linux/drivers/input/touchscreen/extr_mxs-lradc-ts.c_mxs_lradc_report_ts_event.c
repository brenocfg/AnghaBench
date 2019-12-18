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
struct mxs_lradc_ts {int /*<<< orphan*/  ts_input; int /*<<< orphan*/  ts_pressure; int /*<<< orphan*/  ts_y_pos; int /*<<< orphan*/  ts_x_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxs_lradc_report_ts_event(struct mxs_lradc_ts *ts)
{
	input_report_abs(ts->ts_input, ABS_X, ts->ts_x_pos);
	input_report_abs(ts->ts_input, ABS_Y, ts->ts_y_pos);
	input_report_abs(ts->ts_input, ABS_PRESSURE, ts->ts_pressure);
	input_report_key(ts->ts_input, BTN_TOUCH, 1);
	input_sync(ts->ts_input);
}