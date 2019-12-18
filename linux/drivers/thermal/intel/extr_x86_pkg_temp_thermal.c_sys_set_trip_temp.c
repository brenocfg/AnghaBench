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
struct zone_device {int tj_max; int /*<<< orphan*/  cpu; } ;
struct thermal_zone_device {struct zone_device* devdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_NUMBER_OF_TRIPS ; 
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int THERM_INT_THRESHOLD0_ENABLE ; 
 int THERM_INT_THRESHOLD1_ENABLE ; 
 int THERM_MASK_THRESHOLD0 ; 
 int THERM_MASK_THRESHOLD1 ; 
 int THERM_SHIFT_THRESHOLD0 ; 
 int THERM_SHIFT_THRESHOLD1 ; 
 int rdmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int wrmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
sys_set_trip_temp(struct thermal_zone_device *tzd, int trip, int temp)
{
	struct zone_device *zonedev = tzd->devdata;
	u32 l, h, mask, shift, intr;
	int ret;

	if (trip >= MAX_NUMBER_OF_TRIPS || temp >= zonedev->tj_max)
		return -EINVAL;

	ret = rdmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT,
			   &l, &h);
	if (ret < 0)
		return ret;

	if (trip) {
		mask = THERM_MASK_THRESHOLD1;
		shift = THERM_SHIFT_THRESHOLD1;
		intr = THERM_INT_THRESHOLD1_ENABLE;
	} else {
		mask = THERM_MASK_THRESHOLD0;
		shift = THERM_SHIFT_THRESHOLD0;
		intr = THERM_INT_THRESHOLD0_ENABLE;
	}
	l &= ~mask;
	/*
	* When users space sets a trip temperature == 0, which is indication
	* that, it is no longer interested in receiving notifications.
	*/
	if (!temp) {
		l &= ~intr;
	} else {
		l |= (zonedev->tj_max - temp)/1000 << shift;
		l |= intr;
	}

	return wrmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT,
			l, h);
}