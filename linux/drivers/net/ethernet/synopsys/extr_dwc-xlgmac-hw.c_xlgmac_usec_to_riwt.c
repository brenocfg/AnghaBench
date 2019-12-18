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
struct xlgmac_pdata {unsigned long sysclk_rate; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int xlgmac_usec_to_riwt(struct xlgmac_pdata *pdata,
					unsigned int usec)
{
	unsigned long rate;
	unsigned int ret;

	rate = pdata->sysclk_rate;

	/* Convert the input usec value to the watchdog timer value. Each
	 * watchdog timer value is equivalent to 256 clock cycles.
	 * Calculate the required value as:
	 *   ( usec * ( system_clock_mhz / 10^6 ) / 256
	 */
	ret = (usec * (rate / 1000000)) / 256;

	return ret;
}