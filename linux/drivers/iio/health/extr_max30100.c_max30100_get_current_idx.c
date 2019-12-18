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
 int ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 unsigned int* max30100_led_current_mapping ; 

__attribute__((used)) static int max30100_get_current_idx(unsigned int val, int *reg)
{
	int idx;

	/* LED turned off */
	if (val == 0) {
		*reg = 0;
		return 0;
	}

	for (idx = 0; idx < ARRAY_SIZE(max30100_led_current_mapping); idx++) {
		if (max30100_led_current_mapping[idx] == val) {
			*reg = idx + 1;
			return 0;
		}
	}

	return -EINVAL;
}