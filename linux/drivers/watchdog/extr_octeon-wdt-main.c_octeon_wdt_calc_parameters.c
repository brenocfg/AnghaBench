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

/* Variables and functions */
 unsigned int countdown_reset ; 
 int divisor ; 
 int heartbeat ; 
 int max_timeout_sec ; 
 int octeon_get_io_clock_rate () ; 
 int timeout_cnt ; 
 int timeout_sec ; 

__attribute__((used)) static void octeon_wdt_calc_parameters(int t)
{
	unsigned int periods;

	timeout_sec = max_timeout_sec;


	/*
	 * Find the largest interrupt period, that can evenly divide
	 * the requested heartbeat time.
	 */
	while ((t % timeout_sec) != 0)
		timeout_sec--;

	periods = t / timeout_sec;

	/*
	 * The last two periods are after the irq is disabled, and
	 * then to the nmi, so we subtract them off.
	 */

	countdown_reset = periods > 2 ? periods - 2 : 0;
	heartbeat = t;
	timeout_cnt = ((octeon_get_io_clock_rate() / divisor) * timeout_sec) >> 8;
}