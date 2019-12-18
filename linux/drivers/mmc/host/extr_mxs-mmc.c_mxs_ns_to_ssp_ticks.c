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
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static unsigned short mxs_ns_to_ssp_ticks(unsigned clock_rate, unsigned ns)
{
	const unsigned int ssp_timeout_mul = 4096;
	/*
	 * Calculate ticks in ms since ns are large numbers
	 * and might overflow
	 */
	const unsigned int clock_per_ms = clock_rate / 1000;
	const unsigned int ms = ns / 1000;
	const unsigned int ticks = ms * clock_per_ms;
	const unsigned int ssp_ticks = ticks / ssp_timeout_mul;

	WARN_ON(ssp_ticks == 0);
	return ssp_ticks;
}