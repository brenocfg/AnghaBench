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
struct mxs_lradc_ts {scalar_t__ base; int /*<<< orphan*/  cur_plate; } ;

/* Variables and functions */
 scalar_t__ LRADC_CH (int) ; 
 scalar_t__ LRADC_CTRL1 ; 
 int LRADC_CTRL1_LRADC_IRQ (int) ; 
 scalar_t__ LRADC_DELAY (int) ; 
 int LRADC_DELAY_DELAY (int) ; 
 int LRADC_DELAY_KICK ; 
 int LRADC_DELAY_TRIGGER (int) ; 
 int /*<<< orphan*/  LRADC_SAMPLE_VALID ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 int TOUCHSCREEN_VCHANNEL1 ; 
 int TOUCHSCREEN_VCHANNEL2 ; 
 int /*<<< orphan*/  mxs_lradc_setup_touch_detection (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_complete_touch_event(struct mxs_lradc_ts *ts)
{
	mxs_lradc_setup_touch_detection(ts);
	ts->cur_plate = LRADC_SAMPLE_VALID;
	/*
	 * start a dummy conversion to burn time to settle the signals
	 * note: we are not interested in the conversion's value
	 */
	writel(0, ts->base + LRADC_CH(TOUCHSCREEN_VCHANNEL1));
	writel(LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
	       LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	writel(LRADC_DELAY_TRIGGER(1 << TOUCHSCREEN_VCHANNEL1) |
	       LRADC_DELAY_KICK | LRADC_DELAY_DELAY(10),
	       ts->base + LRADC_DELAY(2));
}