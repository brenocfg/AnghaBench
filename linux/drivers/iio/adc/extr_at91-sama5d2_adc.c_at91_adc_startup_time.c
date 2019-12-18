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
 unsigned int ARRAY_SIZE (unsigned int const*) ; 

__attribute__((used)) static unsigned at91_adc_startup_time(unsigned startup_time_min,
				      unsigned adc_clk_khz)
{
	static const unsigned int startup_lookup[] = {
		  0,   8,  16,  24,
		 64,  80,  96, 112,
		512, 576, 640, 704,
		768, 832, 896, 960
		};
	unsigned ticks_min, i;

	/*
	 * Since the adc frequency is checked before, there is no reason
	 * to not meet the startup time constraint.
	 */

	ticks_min = startup_time_min * adc_clk_khz / 1000;
	for (i = 0; i < ARRAY_SIZE(startup_lookup); i++)
		if (startup_lookup[i] > ticks_min)
			break;

	return i;
}