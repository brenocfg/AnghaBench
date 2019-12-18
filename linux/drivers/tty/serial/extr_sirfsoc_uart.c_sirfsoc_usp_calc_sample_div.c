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
 unsigned long SIRF_IOCLK_DIV_MAX ; 
 unsigned short SIRF_MAX_SAMPLE_DIV ; 
 unsigned short SIRF_USP_MIN_SAMPLE_DIV ; 

__attribute__((used)) static unsigned int
sirfsoc_usp_calc_sample_div(unsigned long set_rate,
		unsigned long ioclk_rate, unsigned long *sample_reg)
{
	unsigned long min_delta = ~0UL;
	unsigned short sample_div;
	unsigned long ioclk_div = 0;
	unsigned long temp_delta;

	for (sample_div = SIRF_USP_MIN_SAMPLE_DIV;
			sample_div <= SIRF_MAX_SAMPLE_DIV; sample_div++) {
		temp_delta = ioclk_rate -
		(ioclk_rate + (set_rate * sample_div) / 2)
		/ (set_rate * sample_div) * set_rate * sample_div;

		temp_delta = (temp_delta > 0) ? temp_delta : -temp_delta;
		if (temp_delta < min_delta) {
			ioclk_div = (2 * ioclk_rate /
				(set_rate * sample_div) + 1) / 2 - 1;
			if (ioclk_div > SIRF_IOCLK_DIV_MAX)
				continue;
			min_delta = temp_delta;
			*sample_reg = sample_div;
			if (!temp_delta)
				break;
		}
	}
	return ioclk_div;
}