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
struct max77620_chip {int chip_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX20024 129 
 int MAX20024_FPS_PERIOD_MIN_US ; 
#define  MAX77620 128 
 int MAX77620_FPS_PERIOD_MIN_US ; 

__attribute__((used)) static int max77620_get_fps_period_reg_value(struct max77620_chip *chip,
					     int tperiod)
{
	int fps_min_period;
	int i;

	switch (chip->chip_id) {
	case MAX20024:
		fps_min_period = MAX20024_FPS_PERIOD_MIN_US;
		break;
	case MAX77620:
		fps_min_period = MAX77620_FPS_PERIOD_MIN_US;
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < 7; i++) {
		if (fps_min_period >= tperiod)
			return i;
		fps_min_period *= 2;
	}

	return i;
}