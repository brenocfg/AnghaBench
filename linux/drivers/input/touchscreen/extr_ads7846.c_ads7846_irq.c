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
struct input_dev {int dummy; } ;
struct ads7846 {int pendown; TYPE_1__* spi; struct input_dev* input; int /*<<< orphan*/  stopped; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TS_POLL_DELAY ; 
 int /*<<< orphan*/  TS_POLL_PERIOD ; 
 int /*<<< orphan*/  ads7846_read_state (struct ads7846*) ; 
 int /*<<< orphan*/  ads7846_report_state (struct ads7846*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_pendown_state (struct ads7846*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ads7846_irq(int irq, void *handle)
{
	struct ads7846 *ts = handle;

	/* Start with a small delay before checking pendown state */
	msleep(TS_POLL_DELAY);

	while (!ts->stopped && get_pendown_state(ts)) {

		/* pen is down, continue with the measurement */
		ads7846_read_state(ts);

		if (!ts->stopped)
			ads7846_report_state(ts);

		wait_event_timeout(ts->wait, ts->stopped,
				   msecs_to_jiffies(TS_POLL_PERIOD));
	}

	if (ts->pendown && !ts->stopped) {
		struct input_dev *input = ts->input;

		input_report_key(input, BTN_TOUCH, 0);
		input_report_abs(input, ABS_PRESSURE, 0);
		input_sync(input);

		ts->pendown = false;
		dev_vdbg(&ts->spi->dev, "UP\n");
	}

	return IRQ_HANDLED;
}