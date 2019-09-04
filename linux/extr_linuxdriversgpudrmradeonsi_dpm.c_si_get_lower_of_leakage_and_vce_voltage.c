#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int count; TYPE_1__* entries; } ;
struct si_power_info {TYPE_2__ leakage_voltage; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ voltage; } ;

/* Variables and functions */
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static u16 si_get_lower_of_leakage_and_vce_voltage(struct radeon_device *rdev,
						   u16 vce_voltage)
{
	u16 highest_leakage = 0;
	struct si_power_info *si_pi = si_get_pi(rdev);
	int i;

	for (i = 0; i < si_pi->leakage_voltage.count; i++){
		if (highest_leakage < si_pi->leakage_voltage.entries[i].voltage)
			highest_leakage = si_pi->leakage_voltage.entries[i].voltage;
	}

	if (si_pi->leakage_voltage.count && (highest_leakage < vce_voltage))
		return highest_leakage;

	return vce_voltage;
}