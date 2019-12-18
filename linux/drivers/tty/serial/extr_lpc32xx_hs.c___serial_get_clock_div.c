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
typedef  int u32 ;

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static unsigned int __serial_get_clock_div(unsigned long uartclk,
					   unsigned long rate)
{
	u32 div, goodrate, hsu_rate, l_hsu_rate, comprate;
	u32 rate_diff;

	/* Find the closest divider to get the desired clock rate */
	div = uartclk / rate;
	goodrate = hsu_rate = (div / 14) - 1;
	if (hsu_rate != 0)
		hsu_rate--;

	/* Tweak divider */
	l_hsu_rate = hsu_rate + 3;
	rate_diff = 0xFFFFFFFF;

	while (hsu_rate < l_hsu_rate) {
		comprate = uartclk / ((hsu_rate + 1) * 14);
		if (abs(comprate - rate) < rate_diff) {
			goodrate = hsu_rate;
			rate_diff = abs(comprate - rate);
		}

		hsu_rate++;
	}
	if (hsu_rate > 0xFF)
		hsu_rate = 0xFF;

	return goodrate;
}