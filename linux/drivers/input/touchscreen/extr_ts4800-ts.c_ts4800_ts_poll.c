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
struct ts4800_ts {int pendown; scalar_t__ debounce; scalar_t__ base; } ;
struct input_polled_dev {struct ts4800_ts* private; struct input_dev* input; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ DEBOUNCE_COUNT ; 
 int MAX_12BIT ; 
 int PENDOWN_MASK ; 
 scalar_t__ X_OFFSET ; 
 scalar_t__ Y_OFFSET ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void ts4800_ts_poll(struct input_polled_dev *dev)
{
	struct input_dev *input_dev = dev->input;
	struct ts4800_ts *ts = dev->private;
	u16 last_x = readw(ts->base + X_OFFSET);
	u16 last_y = readw(ts->base + Y_OFFSET);
	bool pendown = last_x & PENDOWN_MASK;

	if (pendown) {
		if (ts->debounce) {
			ts->debounce--;
			return;
		}

		if (!ts->pendown) {
			input_report_key(input_dev, BTN_TOUCH, 1);
			ts->pendown = true;
		}

		last_x = ((~last_x) >> 4) & MAX_12BIT;
		last_y = ((~last_y) >> 4) & MAX_12BIT;

		input_report_abs(input_dev, ABS_X, last_x);
		input_report_abs(input_dev, ABS_Y, last_y);
		input_sync(input_dev);
	} else if (ts->pendown) {
		ts->pendown = false;
		ts->debounce = DEBOUNCE_COUNT;
		input_report_key(input_dev, BTN_TOUCH, 0);
		input_sync(input_dev);
	}
}