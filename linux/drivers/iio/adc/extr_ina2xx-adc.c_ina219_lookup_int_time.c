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
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 int find_closest (unsigned int,unsigned int*,int /*<<< orphan*/ ) ; 
 unsigned int* ina219_conv_time_tab_average ; 
 unsigned int* ina219_conv_time_tab_subsample ; 

__attribute__((used)) static int ina219_lookup_int_time(unsigned int *val_us, int *bits)
{
	if (*val_us > 68100 || *val_us < 84)
		return -EINVAL;

	if (*val_us <= 532) {
		*bits = find_closest(*val_us, ina219_conv_time_tab_subsample,
				    ARRAY_SIZE(ina219_conv_time_tab_subsample));
		*val_us = ina219_conv_time_tab_subsample[*bits];
	} else {
		*bits = find_closest(*val_us, ina219_conv_time_tab_average,
				    ARRAY_SIZE(ina219_conv_time_tab_average));
		*val_us = ina219_conv_time_tab_average[*bits];
		*bits |= 0x8;
	}

	return 0;
}