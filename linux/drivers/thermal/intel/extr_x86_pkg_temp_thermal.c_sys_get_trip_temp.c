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
typedef  unsigned long u32 ;
struct zone_device {unsigned long tj_max; int /*<<< orphan*/  cpu; } ;
struct thermal_zone_device {struct zone_device* devdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_NUMBER_OF_TRIPS ; 
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 unsigned long THERM_MASK_THRESHOLD0 ; 
 unsigned long THERM_MASK_THRESHOLD1 ; 
 unsigned long THERM_SHIFT_THRESHOLD0 ; 
 unsigned long THERM_SHIFT_THRESHOLD1 ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int rdmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int sys_get_trip_temp(struct thermal_zone_device *tzd,
			     int trip, int *temp)
{
	struct zone_device *zonedev = tzd->devdata;
	unsigned long thres_reg_value;
	u32 mask, shift, eax, edx;
	int ret;

	if (trip >= MAX_NUMBER_OF_TRIPS)
		return -EINVAL;

	if (trip) {
		mask = THERM_MASK_THRESHOLD1;
		shift = THERM_SHIFT_THRESHOLD1;
	} else {
		mask = THERM_MASK_THRESHOLD0;
		shift = THERM_SHIFT_THRESHOLD0;
	}

	ret = rdmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT,
			   &eax, &edx);
	if (ret < 0)
		return ret;

	thres_reg_value = (eax & mask) >> shift;
	if (thres_reg_value)
		*temp = zonedev->tj_max - thres_reg_value * 1000;
	else
		*temp = 0;
	pr_debug("sys_get_trip_temp %d\n", *temp);

	return 0;
}