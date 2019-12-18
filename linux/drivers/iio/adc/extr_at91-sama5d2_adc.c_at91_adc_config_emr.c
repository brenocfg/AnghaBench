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
struct at91_adc_state {int oversampling_ratio; } ;

/* Variables and functions */
#define  AT91_OSR_16SAMPLES 130 
#define  AT91_OSR_1SAMPLES 129 
#define  AT91_OSR_4SAMPLES 128 
 int /*<<< orphan*/  AT91_SAMA5D2_EMR ; 
 unsigned int AT91_SAMA5D2_EMR_ASTE (int) ; 
 unsigned int AT91_SAMA5D2_EMR_OSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_SAMA5D2_EMR_OSR_16SAMPLES ; 
 int /*<<< orphan*/  AT91_SAMA5D2_EMR_OSR_1SAMPLES ; 
 int /*<<< orphan*/  AT91_SAMA5D2_EMR_OSR_4SAMPLES ; 
 unsigned int AT91_SAMA5D2_EMR_OSR_MASK ; 
 unsigned int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void at91_adc_config_emr(struct at91_adc_state *st)
{
	/* configure the extended mode register */
	unsigned int emr = at91_adc_readl(st, AT91_SAMA5D2_EMR);

	/* select oversampling per single trigger event */
	emr |= AT91_SAMA5D2_EMR_ASTE(1);

	/* delete leftover content if it's the case */
	emr &= ~AT91_SAMA5D2_EMR_OSR_MASK;

	/* select oversampling ratio from configuration */
	switch (st->oversampling_ratio) {
	case AT91_OSR_1SAMPLES:
		emr |= AT91_SAMA5D2_EMR_OSR(AT91_SAMA5D2_EMR_OSR_1SAMPLES) &
		       AT91_SAMA5D2_EMR_OSR_MASK;
		break;
	case AT91_OSR_4SAMPLES:
		emr |= AT91_SAMA5D2_EMR_OSR(AT91_SAMA5D2_EMR_OSR_4SAMPLES) &
		       AT91_SAMA5D2_EMR_OSR_MASK;
		break;
	case AT91_OSR_16SAMPLES:
		emr |= AT91_SAMA5D2_EMR_OSR(AT91_SAMA5D2_EMR_OSR_16SAMPLES) &
		       AT91_SAMA5D2_EMR_OSR_MASK;
		break;
	}

	at91_adc_writel(st, AT91_SAMA5D2_EMR, emr);
}