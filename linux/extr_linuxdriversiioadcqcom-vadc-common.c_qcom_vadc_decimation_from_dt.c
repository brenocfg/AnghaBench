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
 int EINVAL ; 
 int VADC_DECIMATION_MAX ; 
 int VADC_DECIMATION_MIN ; 
 int __ffs64 (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

int qcom_vadc_decimation_from_dt(u32 value)
{
	if (!is_power_of_2(value) || value < VADC_DECIMATION_MIN ||
	    value > VADC_DECIMATION_MAX)
		return -EINVAL;

	return __ffs64(value / VADC_DECIMATION_MIN);
}