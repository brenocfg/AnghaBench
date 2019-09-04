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
struct tsc200x {int pen_down; int /*<<< orphan*/  dev; int /*<<< orphan*/  idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsc200x_update_pen_state(struct tsc200x *ts,
				     int x, int y, int pressure)
{
	if (pressure) {
		input_report_abs(ts->idev, ABS_X, x);
		input_report_abs(ts->idev, ABS_Y, y);
		input_report_abs(ts->idev, ABS_PRESSURE, pressure);
		if (!ts->pen_down) {
			input_report_key(ts->idev, BTN_TOUCH, !!pressure);
			ts->pen_down = true;
		}
	} else {
		input_report_abs(ts->idev, ABS_PRESSURE, 0);
		if (ts->pen_down) {
			input_report_key(ts->idev, BTN_TOUCH, 0);
			ts->pen_down = false;
		}
	}
	input_sync(ts->idev);
	dev_dbg(ts->dev, "point(%4d,%4d), pressure (%4d)\n", x, y,
		pressure);
}