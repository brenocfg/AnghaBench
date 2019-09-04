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
struct mxs_lradc_ts {int cur_plate; int /*<<< orphan*/  ts_pressure; void* ts_x_pos; void* ts_y_pos; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LRADC_CTRL1 ; 
 int /*<<< orphan*/  LRADC_CTRL1_TOUCH_DETECT_IRQ ; 
#define  LRADC_SAMPLE_PRESSURE 132 
#define  LRADC_SAMPLE_VALID 131 
#define  LRADC_SAMPLE_X 130 
#define  LRADC_SAMPLE_Y 129 
#define  LRADC_TOUCH 128 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL1 ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL2 ; 
 int /*<<< orphan*/  mxs_lradc_check_touch_event (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_complete_touch_event (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_finish_touch_event (struct mxs_lradc_ts*,int) ; 
 int /*<<< orphan*/  mxs_lradc_prepare_pressure (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_prepare_x_pos (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  mxs_lradc_read_ts_pressure (struct mxs_lradc_ts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_lradc_start_touch_event (struct mxs_lradc_ts*) ; 
 void* mxs_lradc_ts_read_raw_channel (struct mxs_lradc_ts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_handle_touch(struct mxs_lradc_ts *ts)
{
	switch (ts->cur_plate) {
	case LRADC_TOUCH:
		if (mxs_lradc_check_touch_event(ts))
			mxs_lradc_start_touch_event(ts);
		writel(LRADC_CTRL1_TOUCH_DETECT_IRQ,
		       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
		return;

	case LRADC_SAMPLE_Y:
		ts->ts_y_pos =
		    mxs_lradc_ts_read_raw_channel(ts, TOUCHSCREEN_VCHANNEL1);
		mxs_lradc_prepare_x_pos(ts);
		return;

	case LRADC_SAMPLE_X:
		ts->ts_x_pos =
		    mxs_lradc_ts_read_raw_channel(ts, TOUCHSCREEN_VCHANNEL1);
		mxs_lradc_prepare_pressure(ts);
		return;

	case LRADC_SAMPLE_PRESSURE:
		ts->ts_pressure =
		    mxs_lradc_read_ts_pressure(ts,
					       TOUCHSCREEN_VCHANNEL2,
					       TOUCHSCREEN_VCHANNEL1);
		mxs_lradc_complete_touch_event(ts);
		return;

	case LRADC_SAMPLE_VALID:
		mxs_lradc_finish_touch_event(ts, 1);
		break;
	}
}