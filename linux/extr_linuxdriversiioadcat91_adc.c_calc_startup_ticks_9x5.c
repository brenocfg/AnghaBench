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
 int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static u32 calc_startup_ticks_9x5(u32 startup_time, u32 adc_clk_khz)
{
	/*
	 * For sama5d3x and at91sam9x5, the formula changes to:
	 * Startup Time = <lookup_table_value> / ADC Clock
	 */
	static const int startup_lookup[] = {
		0,   8,   16,  24,
		64,  80,  96,  112,
		512, 576, 640, 704,
		768, 832, 896, 960
		};
	int i, size = ARRAY_SIZE(startup_lookup);
	unsigned int ticks;

	ticks = startup_time * adc_clk_khz / 1000;
	for (i = 0; i < size; i++)
		if (ticks < startup_lookup[i])
			break;

	ticks = i;
	if (ticks == size)
		/* Reach the end of lookup table */
		ticks = size - 1;

	return ticks;
}