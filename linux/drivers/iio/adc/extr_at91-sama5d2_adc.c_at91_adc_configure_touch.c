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
typedef  int u16 ;
struct TYPE_2__ {void* sample_period_val; } ;
struct at91_adc_state {int current_sample_rate; TYPE_1__ touch_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_ACR ; 
 int AT91_SAMA5D2_ACR_PENDETSENS_MASK ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IDR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IER ; 
 int AT91_SAMA5D2_IER_NOPEN ; 
 int AT91_SAMA5D2_IER_PEN ; 
 int AT91_SAMA5D2_TOUCH_PEN_DETECT_DEBOUNCE_US ; 
 int AT91_SAMA5D2_TOUCH_SAMPLE_PERIOD_US ; 
 int /*<<< orphan*/  AT91_SAMA5D2_TSMR ; 
 int AT91_SAMA5D2_TSMR_NOTSDMA ; 
 int AT91_SAMA5D2_TSMR_PENDBC (int) ; 
 int AT91_SAMA5D2_TSMR_PENDBC_MASK ; 
 int AT91_SAMA5D2_TSMR_PENDET_ENA ; 
 int AT91_SAMA5D2_TSMR_TSAV (int) ; 
 int AT91_SAMA5D2_TSMR_TSAV_MASK ; 
 int AT91_SAMA5D2_TSMR_TSFREQ (int) ; 
 int AT91_SAMA5D2_TSMR_TSFREQ_MASK ; 
 int AT91_SAMA5D2_TSMR_TSMODE_4WIRE_PRESS ; 
 int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 
 void* round_up (int,int) ; 

__attribute__((used)) static int at91_adc_configure_touch(struct at91_adc_state *st, bool state)
{
	u32 clk_khz = st->current_sample_rate / 1000;
	int i = 0;
	u16 pendbc;
	u32 tsmr, acr;

	if (!state) {
		/* disabling touch IRQs and setting mode to no touch enabled */
		at91_adc_writel(st, AT91_SAMA5D2_IDR,
				AT91_SAMA5D2_IER_PEN | AT91_SAMA5D2_IER_NOPEN);
		at91_adc_writel(st, AT91_SAMA5D2_TSMR, 0);
		return 0;
	}
	/*
	 * debounce time is in microseconds, we need it in milliseconds to
	 * multiply with kilohertz, so, divide by 1000, but after the multiply.
	 * round up to make sure pendbc is at least 1
	 */
	pendbc = round_up(AT91_SAMA5D2_TOUCH_PEN_DETECT_DEBOUNCE_US *
			  clk_khz / 1000, 1);

	/* get the required exponent */
	while (pendbc >> i++)
		;

	pendbc = i;

	tsmr = AT91_SAMA5D2_TSMR_TSMODE_4WIRE_PRESS;

	tsmr |= AT91_SAMA5D2_TSMR_TSAV(2) & AT91_SAMA5D2_TSMR_TSAV_MASK;
	tsmr |= AT91_SAMA5D2_TSMR_PENDBC(pendbc) &
		AT91_SAMA5D2_TSMR_PENDBC_MASK;
	tsmr |= AT91_SAMA5D2_TSMR_NOTSDMA;
	tsmr |= AT91_SAMA5D2_TSMR_PENDET_ENA;
	tsmr |= AT91_SAMA5D2_TSMR_TSFREQ(2) & AT91_SAMA5D2_TSMR_TSFREQ_MASK;

	at91_adc_writel(st, AT91_SAMA5D2_TSMR, tsmr);

	acr =  at91_adc_readl(st, AT91_SAMA5D2_ACR);
	acr &= ~AT91_SAMA5D2_ACR_PENDETSENS_MASK;
	acr |= 0x02 & AT91_SAMA5D2_ACR_PENDETSENS_MASK;
	at91_adc_writel(st, AT91_SAMA5D2_ACR, acr);

	/* Sample Period Time = (TRGPER + 1) / ADCClock */
	st->touch_st.sample_period_val =
				 round_up((AT91_SAMA5D2_TOUCH_SAMPLE_PERIOD_US *
				 clk_khz / 1000) - 1, 1);
	/* enable pen detect IRQ */
	at91_adc_writel(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_PEN);

	return 0;
}