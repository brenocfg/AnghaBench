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
struct mxs_lradc_ts {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LRADC_CTRL1 ; 
 int /*<<< orphan*/  LRADC_CTRL1_LRADC_IRQ_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LRADC_CTRL1_TOUCH_DETECT_IRQ_EN ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL1 ; 
 int /*<<< orphan*/  mxs_lradc_prepare_y_pos (struct mxs_lradc_ts*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_start_touch_event(struct mxs_lradc_ts *ts)
{
	writel(LRADC_CTRL1_TOUCH_DETECT_IRQ_EN,
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	writel(LRADC_CTRL1_LRADC_IRQ_EN(TOUCHSCREEN_VCHANNEL1),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
	/*
	 * start with the Y-pos, because it uses nearly the same plate
	 * settings like the touch detection
	 */
	mxs_lradc_prepare_y_pos(ts);
}