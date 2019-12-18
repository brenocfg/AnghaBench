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
struct platform_pwm_backlight_data {int max_brightness; unsigned int* levels; } ;

/* Variables and functions */
 unsigned int abs (unsigned int) ; 

__attribute__((used)) static bool pwm_backlight_is_linear(struct platform_pwm_backlight_data *data)
{
	unsigned int nlevels = data->max_brightness + 1;
	unsigned int min_val = data->levels[0];
	unsigned int max_val = data->levels[nlevels - 1];
	/*
	 * Multiplying by 128 means that even in pathological cases such
	 * as (max_val - min_val) == nlevels the error at max_val is less
	 * than 1%.
	 */
	unsigned int slope = (128 * (max_val - min_val)) / nlevels;
	unsigned int margin = (max_val - min_val) / 20; /* 5% */
	int i;

	for (i = 1; i < nlevels; i++) {
		unsigned int linear_value = min_val + ((i * slope) / 128);
		unsigned int delta = abs(linear_value - data->levels[i]);

		if (delta > margin)
			return false;
	}

	return true;
}