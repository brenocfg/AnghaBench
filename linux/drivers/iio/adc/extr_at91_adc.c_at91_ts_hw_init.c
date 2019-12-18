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
typedef  int u32 ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct at91_adc_state {int ts_pendbc; scalar_t__ touchscreen_type; void* ts_sample_period_val; TYPE_1__* caps; } ;
struct TYPE_2__ {int ts_pen_detect_sensitivity; int /*<<< orphan*/  ts_filter_average; int /*<<< orphan*/  has_tsmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ADC_ACR ; 
 int AT91_ADC_ACR_PENDETSENS ; 
 int /*<<< orphan*/  AT91_ADC_MR ; 
 int AT91_ADC_PENDBC ; 
 int AT91_ADC_PENDBC_ (int) ; 
 int AT91_ADC_PENDET ; 
 int AT91_ADC_TSAMOD_TS_ONLY_MODE ; 
 int /*<<< orphan*/  AT91_ADC_TSMR ; 
 int AT91_ADC_TSMR_NOTSDMA ; 
 int AT91_ADC_TSMR_PENDBC ; 
 int AT91_ADC_TSMR_PENDBC_ (int) ; 
 int AT91_ADC_TSMR_PENDET_ENA ; 
 int AT91_ADC_TSMR_SCTIM ; 
 int AT91_ADC_TSMR_SCTIM_ (int) ; 
 int AT91_ADC_TSMR_TSAV ; 
 int AT91_ADC_TSMR_TSAV_ (int /*<<< orphan*/ ) ; 
 int AT91_ADC_TSMR_TSMODE_4WIRE_PRESS ; 
 int AT91_ADC_TSMR_TSMODE_5WIRE ; 
 int /*<<< orphan*/  AT91_ADC_TSR ; 
 int AT91_ADC_TSR_SHTIM ; 
 int AT91_ADC_TSR_SHTIM_ (int /*<<< orphan*/ ) ; 
 scalar_t__ ATMEL_ADC_TOUCHSCREEN_4WIRE ; 
 int DIV_ROUND_UP (int,int) ; 
 int TOUCH_PEN_DETECT_DEBOUNCE_US ; 
 int TOUCH_SAMPLE_PERIOD_US ; 
 int TOUCH_SAMPLE_PERIOD_US_RL ; 
 int TOUCH_SCTIM_US ; 
 int /*<<< orphan*/  TOUCH_SHTIM ; 
 scalar_t__ abs (int) ; 
 int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 struct iio_dev* iio_priv_to_dev (struct at91_adc_state*) ; 
 void* round_up (int,int) ; 

__attribute__((used)) static int at91_ts_hw_init(struct at91_adc_state *st, u32 adc_clk_khz)
{
	struct iio_dev *idev = iio_priv_to_dev(st);
	u32 reg = 0;
	u32 tssctim = 0;
	int i = 0;

	/* a Pen Detect Debounce Time is necessary for the ADC Touch to avoid
	 * pen detect noise.
	 * The formula is : Pen Detect Debounce Time = (2 ^ pendbc) / ADCClock
	 */
	st->ts_pendbc = round_up(TOUCH_PEN_DETECT_DEBOUNCE_US * adc_clk_khz /
				 1000, 1);

	while (st->ts_pendbc >> ++i)
		;	/* Empty! Find the shift offset */
	if (abs(st->ts_pendbc - (1 << i)) < abs(st->ts_pendbc - (1 << (i - 1))))
		st->ts_pendbc = i;
	else
		st->ts_pendbc = i - 1;

	if (!st->caps->has_tsmr) {
		reg = at91_adc_readl(st, AT91_ADC_MR);
		reg |= AT91_ADC_TSAMOD_TS_ONLY_MODE | AT91_ADC_PENDET;

		reg |= AT91_ADC_PENDBC_(st->ts_pendbc) & AT91_ADC_PENDBC;
		at91_adc_writel(st, AT91_ADC_MR, reg);

		reg = AT91_ADC_TSR_SHTIM_(TOUCH_SHTIM) & AT91_ADC_TSR_SHTIM;
		at91_adc_writel(st, AT91_ADC_TSR, reg);

		st->ts_sample_period_val = round_up((TOUCH_SAMPLE_PERIOD_US_RL *
						    adc_clk_khz / 1000) - 1, 1);

		return 0;
	}

	/* Touchscreen Switches Closure time needed for allowing the value to
	 * stabilize.
	 * Switch Closure Time = (TSSCTIM * 4) ADCClock periods
	 */
	tssctim = DIV_ROUND_UP(TOUCH_SCTIM_US * adc_clk_khz / 1000, 4);
	dev_dbg(&idev->dev, "adc_clk at: %d KHz, tssctim at: %d\n",
		adc_clk_khz, tssctim);

	if (st->touchscreen_type == ATMEL_ADC_TOUCHSCREEN_4WIRE)
		reg = AT91_ADC_TSMR_TSMODE_4WIRE_PRESS;
	else
		reg = AT91_ADC_TSMR_TSMODE_5WIRE;

	reg |= AT91_ADC_TSMR_SCTIM_(tssctim) & AT91_ADC_TSMR_SCTIM;
	reg |= AT91_ADC_TSMR_TSAV_(st->caps->ts_filter_average)
	       & AT91_ADC_TSMR_TSAV;
	reg |= AT91_ADC_TSMR_PENDBC_(st->ts_pendbc) & AT91_ADC_TSMR_PENDBC;
	reg |= AT91_ADC_TSMR_NOTSDMA;
	reg |= AT91_ADC_TSMR_PENDET_ENA;
	reg |= 0x03 << 8;	/* TSFREQ, needs to be bigger than TSAV */

	at91_adc_writel(st, AT91_ADC_TSMR, reg);

	/* Change adc internal resistor value for better pen detection,
	 * default value is 100 kOhm.
	 * 0 = 200 kOhm, 1 = 150 kOhm, 2 = 100 kOhm, 3 = 50 kOhm
	 * option only available on ES2 and higher
	 */
	at91_adc_writel(st, AT91_ADC_ACR, st->caps->ts_pen_detect_sensitivity
			& AT91_ADC_ACR_PENDETSENS);

	/* Sample Period Time = (TRGPER + 1) / ADCClock */
	st->ts_sample_period_val = round_up((TOUCH_SAMPLE_PERIOD_US *
			adc_clk_khz / 1000) - 1, 1);

	return 0;
}