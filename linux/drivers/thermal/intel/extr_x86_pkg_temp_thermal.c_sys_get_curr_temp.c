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
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_STATUS ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  rdmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int sys_get_curr_temp(struct thermal_zone_device *tzd, int *temp)
{
	struct zone_device *zonedev = tzd->devdata;
	u32 eax, edx;

	rdmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_STATUS,
			&eax, &edx);
	if (eax & 0x80000000) {
		*temp = zonedev->tj_max - ((eax >> 16) & 0x7f) * 1000;
		pr_debug("sys_get_curr_temp %d\n", *temp);
		return 0;
	}
	return -EINVAL;
}