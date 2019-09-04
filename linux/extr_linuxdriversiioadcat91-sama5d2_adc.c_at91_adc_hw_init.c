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
struct TYPE_2__ {int /*<<< orphan*/  min_sample_rate; } ;
struct at91_adc_state {TYPE_1__ soc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_CR ; 
 int AT91_SAMA5D2_CR_SWRST ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IDR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_MR ; 
 int AT91_SAMA5D2_MR_ANACH ; 
 int AT91_SAMA5D2_MR_TRANSFER (int) ; 
 int /*<<< orphan*/  at91_adc_config_emr (struct at91_adc_state*) ; 
 int /*<<< orphan*/  at91_adc_setup_samp_freq (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91_adc_hw_init(struct at91_adc_state *st)
{
	at91_adc_writel(st, AT91_SAMA5D2_CR, AT91_SAMA5D2_CR_SWRST);
	at91_adc_writel(st, AT91_SAMA5D2_IDR, 0xffffffff);
	/*
	 * Transfer field must be set to 2 according to the datasheet and
	 * allows different analog settings for each channel.
	 */
	at91_adc_writel(st, AT91_SAMA5D2_MR,
			AT91_SAMA5D2_MR_TRANSFER(2) | AT91_SAMA5D2_MR_ANACH);

	at91_adc_setup_samp_freq(st, st->soc_info.min_sample_rate);

	/* configure extended mode register */
	at91_adc_config_emr(st);
}