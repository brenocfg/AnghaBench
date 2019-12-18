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
 unsigned int SIRF_IOCLK_DIV_MASK ; 
 unsigned long SIRF_IOCLK_DIV_MAX ; 
 unsigned short SIRF_MAX_SAMPLE_DIV ; 
 unsigned short SIRF_MIN_SAMPLE_DIV ; 
 unsigned int SIRF_SAMPLE_DIV_MASK ; 
 unsigned short SIRF_SAMPLE_DIV_SHIFT ; 

__attribute__((used)) static unsigned int
sirfsoc_uart_calc_sample_div(unsigned long baud_rate,
			unsigned long ioclk_rate, unsigned long *set_baud)
{
	unsigned long min_delta = ~0UL;
	unsigned short sample_div;
	unsigned int regv = 0;
	unsigned long ioclk_div;
	unsigned long baud_tmp;
	int temp_delta;

	for (sample_div = SIRF_MIN_SAMPLE_DIV;
			sample_div <= SIRF_MAX_SAMPLE_DIV; sample_div++) {
		ioclk_div = (ioclk_rate / (baud_rate * (sample_div + 1))) - 1;
		if (ioclk_div > SIRF_IOCLK_DIV_MAX)
			continue;
		baud_tmp = ioclk_rate / ((ioclk_div + 1) * (sample_div + 1));
		temp_delta = baud_tmp - baud_rate;
		temp_delta = (temp_delta > 0) ? temp_delta : -temp_delta;
		if (temp_delta < min_delta) {
			regv = regv & (~SIRF_IOCLK_DIV_MASK);
			regv = regv | ioclk_div;
			regv = regv & (~SIRF_SAMPLE_DIV_MASK);
			regv = regv | (sample_div << SIRF_SAMPLE_DIV_SHIFT);
			min_delta = temp_delta;
			*set_baud = baud_tmp;
		}
	}
	return regv;
}