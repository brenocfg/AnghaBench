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
typedef  unsigned long u32 ;
struct tsl2563_lux_coeff {unsigned long ch_ratio; unsigned long ch0_coeff; unsigned long ch1_coeff; } ;

/* Variables and functions */
 unsigned long ADC_FRAC_BITS ; 
 unsigned long ULONG_MAX ; 
 struct tsl2563_lux_coeff* lux_table ; 

__attribute__((used)) static unsigned int tsl2563_adc_to_lux(u32 adc0, u32 adc1)
{
	const struct tsl2563_lux_coeff *lp = lux_table;
	unsigned long ratio, lux, ch0 = adc0, ch1 = adc1;

	ratio = ch0 ? ((ch1 << ADC_FRAC_BITS) / ch0) : ULONG_MAX;

	while (lp->ch_ratio < ratio)
		lp++;

	lux = ch0 * lp->ch0_coeff - ch1 * lp->ch1_coeff;

	return (unsigned int) (lux >> ADC_FRAC_BITS);
}