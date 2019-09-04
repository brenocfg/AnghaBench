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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  startup_time; } ;
struct at91_adc_state {unsigned int current_sample_rate; TYPE_1__ soc_info; int /*<<< orphan*/  per_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_MR ; 
 unsigned int AT91_SAMA5D2_MR_PRESCAL (unsigned int) ; 
 unsigned int AT91_SAMA5D2_MR_PRESCAL_MASK ; 
 unsigned int AT91_SAMA5D2_MR_STARTUP (unsigned int) ; 
 unsigned int AT91_SAMA5D2_MR_STARTUP_MASK ; 
 unsigned int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 unsigned int at91_adc_startup_time (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 struct iio_dev* iio_priv_to_dev (struct at91_adc_state*) ; 

__attribute__((used)) static void at91_adc_setup_samp_freq(struct at91_adc_state *st, unsigned freq)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	unsigned f_per, prescal, startup, mr;

	f_per = clk_get_rate(st->per_clk);
	prescal = (f_per / (2 * freq)) - 1;

	startup = at91_adc_startup_time(st->soc_info.startup_time,
					freq / 1000);

	mr = at91_adc_readl(st, AT91_SAMA5D2_MR);
	mr &= ~(AT91_SAMA5D2_MR_STARTUP_MASK | AT91_SAMA5D2_MR_PRESCAL_MASK);
	mr |= AT91_SAMA5D2_MR_STARTUP(startup);
	mr |= AT91_SAMA5D2_MR_PRESCAL(prescal);
	at91_adc_writel(st, AT91_SAMA5D2_MR, mr);

	dev_dbg(&indio_dev->dev, "freq: %u, startup: %u, prescal: %u\n",
		freq, startup, prescal);
	st->current_sample_rate = freq;
}