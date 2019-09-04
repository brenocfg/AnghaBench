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
struct iio_dev {int dummy; } ;
struct at91_adc_state {int ts_bufferedmeasure; int ts_prev_absx; int ts_prev_absy; scalar_t__ ts_input; TYPE_1__* registers; int /*<<< orphan*/  ts_pendbc; int /*<<< orphan*/  ts_sample_period_val; scalar_t__ num_channels; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  trigger_register; int /*<<< orphan*/  status_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int AT91RL_ADC_IER_NOPEN ; 
 int AT91RL_ADC_IER_PEN ; 
 int /*<<< orphan*/  AT91_ADC_CHAN (struct at91_adc_state*,int) ; 
 int AT91_ADC_EOC (int) ; 
 int /*<<< orphan*/  AT91_ADC_IDR ; 
 int /*<<< orphan*/  AT91_ADC_IER ; 
 int /*<<< orphan*/  AT91_ADC_IMR ; 
 int /*<<< orphan*/  AT91_ADC_MR ; 
 unsigned int AT91_ADC_PENDBC ; 
 unsigned int AT91_ADC_PENDBC_ (int /*<<< orphan*/ ) ; 
 int AT91_ADC_TRGR_MOD_PERIOD_TRIG ; 
 int AT91_ADC_TRGR_NONE ; 
 int AT91_ADC_TRGR_TRGPER_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX_RLPOS_BITS ; 
 int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handle_adc_eoc_trigger (int,struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  input_report_abs (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 

__attribute__((used)) static irqreturn_t at91_adc_rl_interrupt(int irq, void *private)
{
	struct iio_dev *idev = private;
	struct at91_adc_state *st = iio_priv(idev);
	u32 status = at91_adc_readl(st, st->registers->status_register);
	unsigned int reg;

	status &= at91_adc_readl(st, AT91_ADC_IMR);
	if (status & GENMASK(st->num_channels - 1, 0))
		handle_adc_eoc_trigger(irq, idev);

	if (status & AT91RL_ADC_IER_PEN) {
		/* Disabling pen debounce is required to get a NOPEN irq */
		reg = at91_adc_readl(st, AT91_ADC_MR);
		reg &= ~AT91_ADC_PENDBC;
		at91_adc_writel(st, AT91_ADC_MR, reg);

		at91_adc_writel(st, AT91_ADC_IDR, AT91RL_ADC_IER_PEN);
		at91_adc_writel(st, AT91_ADC_IER, AT91RL_ADC_IER_NOPEN
				| AT91_ADC_EOC(3));
		/* Set up period trigger for sampling */
		at91_adc_writel(st, st->registers->trigger_register,
			AT91_ADC_TRGR_MOD_PERIOD_TRIG |
			AT91_ADC_TRGR_TRGPER_(st->ts_sample_period_val));
	} else if (status & AT91RL_ADC_IER_NOPEN) {
		reg = at91_adc_readl(st, AT91_ADC_MR);
		reg |= AT91_ADC_PENDBC_(st->ts_pendbc) & AT91_ADC_PENDBC;
		at91_adc_writel(st, AT91_ADC_MR, reg);
		at91_adc_writel(st, st->registers->trigger_register,
			AT91_ADC_TRGR_NONE);

		at91_adc_writel(st, AT91_ADC_IDR, AT91RL_ADC_IER_NOPEN
				| AT91_ADC_EOC(3));
		at91_adc_writel(st, AT91_ADC_IER, AT91RL_ADC_IER_PEN);
		st->ts_bufferedmeasure = false;
		input_report_key(st->ts_input, BTN_TOUCH, 0);
		input_sync(st->ts_input);
	} else if (status & AT91_ADC_EOC(3) && st->ts_input) {
		/* Conversion finished and we've a touchscreen */
		if (st->ts_bufferedmeasure) {
			/*
			 * Last measurement is always discarded, since it can
			 * be erroneous.
			 * Always report previous measurement
			 */
			input_report_abs(st->ts_input, ABS_X, st->ts_prev_absx);
			input_report_abs(st->ts_input, ABS_Y, st->ts_prev_absy);
			input_report_key(st->ts_input, BTN_TOUCH, 1);
			input_sync(st->ts_input);
		} else
			st->ts_bufferedmeasure = true;

		/* Now make new measurement */
		st->ts_prev_absx = at91_adc_readl(st, AT91_ADC_CHAN(st, 3))
				   << MAX_RLPOS_BITS;
		st->ts_prev_absx /= at91_adc_readl(st, AT91_ADC_CHAN(st, 2));

		st->ts_prev_absy = at91_adc_readl(st, AT91_ADC_CHAN(st, 1))
				   << MAX_RLPOS_BITS;
		st->ts_prev_absy /= at91_adc_readl(st, AT91_ADC_CHAN(st, 0));
	}

	return IRQ_HANDLED;
}