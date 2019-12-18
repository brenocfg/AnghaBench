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
typedef  size_t u8 ;

/* Variables and functions */

void
wlc_phy_mcs_to_ofdm_powers_nphy(u8 *power, u8 rate_ofdm_start,
				u8 rate_ofdm_end, u8 rate_mcs_start)
{
	u8 rate1, rate2;

	for (rate1 = rate_ofdm_start, rate2 = rate_mcs_start;
	     rate1 <= rate_ofdm_end; rate1++, rate2++) {
		power[rate1] = power[rate2];
		if (rate1 == rate_ofdm_start)
			power[++rate1] = power[rate2];
	}
}