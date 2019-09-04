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
struct mxs_lradc_ts {scalar_t__ base; scalar_t__ settling_delay; scalar_t__ over_sample_delay; scalar_t__ over_sample_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ LRADC_CH (unsigned int) ; 
 int LRADC_CH_ACCUMULATE ; 
 int LRADC_CH_NUM_SAMPLES (scalar_t__) ; 
 int LRADC_CH_VALUE_MASK ; 
 scalar_t__ LRADC_CTRL1 ; 
 int LRADC_CTRL1_LRADC_IRQ (unsigned int) ; 
 scalar_t__ LRADC_DELAY (int) ; 
 int LRADC_DELAY_DELAY (scalar_t__) ; 
 int LRADC_DELAY_KICK ; 
 int LRADC_DELAY_LOOP (scalar_t__) ; 
 int LRADC_DELAY_TRIGGER (int) ; 
 int LRADC_DELAY_TRIGGER_DELAYS (int /*<<< orphan*/ ) ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_setup_ts_channel(struct mxs_lradc_ts *ts, unsigned int ch)
{
	/*
	 * prepare for oversampling conversion
	 *
	 * from the datasheet:
	 * "The ACCUMULATE bit in the appropriate channel register
	 * HW_LRADC_CHn must be set to 1 if NUM_SAMPLES is greater then 0;
	 * otherwise, the IRQs will not fire."
	 */
	writel(LRADC_CH_ACCUMULATE |
	       LRADC_CH_NUM_SAMPLES(ts->over_sample_cnt - 1),
	       ts->base + LRADC_CH(ch));

	/* from the datasheet:
	 * "Software must clear this register in preparation for a
	 * multi-cycle accumulation.
	 */
	writel(LRADC_CH_VALUE_MASK,
	       ts->base + LRADC_CH(ch) + STMP_OFFSET_REG_CLR);

	/*
	 * prepare the delay/loop unit according to the oversampling count
	 *
	 * from the datasheet:
	 * "The DELAY fields in HW_LRADC_DELAY0, HW_LRADC_DELAY1,
	 * HW_LRADC_DELAY2, and HW_LRADC_DELAY3 must be non-zero; otherwise,
	 * the LRADC will not trigger the delay group."
	 */
	writel(LRADC_DELAY_TRIGGER(1 << ch) | LRADC_DELAY_TRIGGER_DELAYS(0) |
	       LRADC_DELAY_LOOP(ts->over_sample_cnt - 1) |
	       LRADC_DELAY_DELAY(ts->over_sample_delay - 1),
	       ts->base + LRADC_DELAY(3));

	writel(LRADC_CTRL1_LRADC_IRQ(ch),
	       ts->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	/*
	 * after changing the touchscreen plates setting
	 * the signals need some initial time to settle. Start the
	 * SoC's delay unit and start the conversion later
	 * and automatically.
	 */
	writel(LRADC_DELAY_TRIGGER(0) | LRADC_DELAY_TRIGGER_DELAYS(BIT(3)) |
	       LRADC_DELAY_KICK | LRADC_DELAY_DELAY(ts->settling_delay),
	       ts->base + LRADC_DELAY(2));
}