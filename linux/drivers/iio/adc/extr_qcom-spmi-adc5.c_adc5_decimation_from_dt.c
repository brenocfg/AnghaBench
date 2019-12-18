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
 unsigned int ADC5_DECIMATION_SAMPLES_MAX ; 
 int EINVAL ; 

__attribute__((used)) static int adc5_decimation_from_dt(u32 value,
					const unsigned int *decimation)
{
	unsigned int i;

	for (i = 0; i < ADC5_DECIMATION_SAMPLES_MAX; i++) {
		if (value == decimation[i])
			return i;
	}

	return -EINVAL;
}