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
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int octeon_get_io_clock_rate () ; 

__attribute__((used)) static unsigned int ns_to_tim_reg(unsigned int tim_mult, unsigned int nsecs)
{
	unsigned int val;

	/*
	 * Compute # of eclock periods to get desired duration in
	 * nanoseconds.
	 */
	val = DIV_ROUND_UP(nsecs * (octeon_get_io_clock_rate() / 1000000),
			  1000 * tim_mult);

	return val;
}