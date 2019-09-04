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
struct at91_adc_state {scalar_t__ oversampling_ratio; } ;

/* Variables and functions */
 scalar_t__ AT91_OSR_1SAMPLES ; 
 scalar_t__ AT91_OSR_4SAMPLES ; 
 int IIO_VAL_INT ; 

__attribute__((used)) static int at91_adc_adjust_val_osr(struct at91_adc_state *st, int *val)
{
	if (st->oversampling_ratio == AT91_OSR_1SAMPLES) {
		/*
		 * in this case we only have 12 bits of real data, but channel
		 * is registered as 14 bits, so shift left two bits
		 */
		*val <<= 2;
	} else if (st->oversampling_ratio == AT91_OSR_4SAMPLES) {
		/*
		 * in this case we have 13 bits of real data, but channel
		 * is registered as 14 bits, so left shift one bit
		 */
		*val <<= 1;
	}

	return IIO_VAL_INT;
}