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
struct mxs_lradc_ts {int ts_valid; scalar_t__ base; int /*<<< orphan*/  cur_plate; int /*<<< orphan*/  ts_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ LRADC_CTRL1 ; 
 int LRADC_CTRL1_LRADC_IRQ (int /*<<< orphan*/ ) ; 
 int LRADC_CTRL1_LRADC_IRQ_EN (int /*<<< orphan*/ ) ; 
 int LRADC_CTRL1_TOUCH_DETECT_IRQ ; 
 int LRADC_CTRL1_TOUCH_DETECT_IRQ_EN ; 
 scalar_t__ LRADC_DELAY (int) ; 
 int /*<<< orphan*/  LRADC_TOUCH ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL1 ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ mxs_lradc_check_touch_event (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_prepare_y_pos (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_report_ts_event (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_finish_touch_event(struct mxs_lradc_ts *ts, bool valid)
{
	/* if it is still touched, report the sample */
	if (valid && mxs_lradc_check_touch_event(ts)) {
		ts->ts_valid = true;
		mxs_lradc_report_ts_event(ts);
	}

	/* if it is even still touched, continue with the next measurement */
	if (mxs_lradc_check_touch_event(ts)) {
		mxs_lradc_prepare_y_pos(ts);
		return;
	}

	if (ts->ts_valid) {
		/* signal the release */
		ts->ts_valid = false;
		input_report_key(ts->ts_input, BTN_TOUCH, 0);
		input_sync(ts->ts_input);
	}

	/* if it is released, wait for the next touch via IRQ */
	ts->cur_plate = LRADC_TOUCH;
	writel(0, ts->base + LRADC_DELAY(2));
	writel(0, ts->base + LRADC_DELAY(3));
	writel(LRADC_CTRL1_TOUCH_DETECT_IRQ |
	       LRADC_CTRL1_LRADC_IRQ_EN(TOUCHSCREEN_VCHANNEL1) |
	       LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	writel(LRADC_CTRL1_TOUCH_DETECT_IRQ_EN,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
}