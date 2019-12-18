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
typedef  unsigned int const u32 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int VADC_HW_SETTLE_SAMPLES_MAX ; 

__attribute__((used)) static int adc5_hw_settle_time_from_dt(u32 value,
					const unsigned int *hw_settle)
{
	unsigned int i;

	for (i = 0; i < VADC_HW_SETTLE_SAMPLES_MAX; i++) {
		if (value == hw_settle[i])
			return i;
	}

	return -EINVAL;
}