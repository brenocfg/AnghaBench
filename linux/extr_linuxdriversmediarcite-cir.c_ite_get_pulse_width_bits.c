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
 unsigned int ITE_HCF_MAX_CARRIER_FREQ ; 
 unsigned int ITE_LCF_MIN_CARRIER_FREQ ; 
 int /*<<< orphan*/  ITE_TXMPW_A ; 
 int /*<<< orphan*/  ITE_TXMPW_B ; 
 int /*<<< orphan*/  ITE_TXMPW_C ; 
 int /*<<< orphan*/  ITE_TXMPW_D ; 
 int /*<<< orphan*/  ITE_TXMPW_E ; 
 scalar_t__ ite_is_high_carrier_freq (unsigned int) ; 

__attribute__((used)) static u8 ite_get_pulse_width_bits(unsigned int freq, int duty_cycle)
{
	unsigned long period_ns, on_ns;

	/* sanitize freq into range */
	if (freq < ITE_LCF_MIN_CARRIER_FREQ)
		freq = ITE_LCF_MIN_CARRIER_FREQ;
	if (freq > ITE_HCF_MAX_CARRIER_FREQ)
		freq = ITE_HCF_MAX_CARRIER_FREQ;

	period_ns = 1000000000UL / freq;
	on_ns = period_ns * duty_cycle / 100;

	if (ite_is_high_carrier_freq(freq)) {
		if (on_ns < 750)
			return ITE_TXMPW_A;

		else if (on_ns < 850)
			return ITE_TXMPW_B;

		else if (on_ns < 950)
			return ITE_TXMPW_C;

		else if (on_ns < 1080)
			return ITE_TXMPW_D;

		else
			return ITE_TXMPW_E;
	} else {
		if (on_ns < 6500)
			return ITE_TXMPW_A;

		else if (on_ns < 7850)
			return ITE_TXMPW_B;

		else if (on_ns < 9650)
			return ITE_TXMPW_C;

		else if (on_ns < 11950)
			return ITE_TXMPW_D;

		else
			return ITE_TXMPW_E;
	}
}