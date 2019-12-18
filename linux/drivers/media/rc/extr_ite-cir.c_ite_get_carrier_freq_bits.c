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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int /*<<< orphan*/  ITE_CFQ_400 ; 
 int /*<<< orphan*/  ITE_CFQ_450 ; 
 int /*<<< orphan*/  ITE_CFQ_480 ; 
 int /*<<< orphan*/  ITE_CFQ_500 ; 
 unsigned int ITE_LCF_MAX_CARRIER_FREQ ; 
 unsigned int ITE_LCF_MIN_CARRIER_FREQ ; 
 scalar_t__ ite_is_high_carrier_freq (unsigned int) ; 

__attribute__((used)) static u8 ite_get_carrier_freq_bits(unsigned int freq)
{
	if (ite_is_high_carrier_freq(freq)) {
		if (freq < 425000)
			return ITE_CFQ_400;

		else if (freq < 465000)
			return ITE_CFQ_450;

		else if (freq < 490000)
			return ITE_CFQ_480;

		else
			return ITE_CFQ_500;
	} else {
			/* trim to limits */
		if (freq < ITE_LCF_MIN_CARRIER_FREQ)
			freq = ITE_LCF_MIN_CARRIER_FREQ;
		if (freq > ITE_LCF_MAX_CARRIER_FREQ)
			freq = ITE_LCF_MAX_CARRIER_FREQ;

		/* convert to kHz and subtract the base freq */
		freq =
		    DIV_ROUND_CLOSEST(freq - ITE_LCF_MIN_CARRIER_FREQ,
				      1000);

		return (u8) freq;
	}
}