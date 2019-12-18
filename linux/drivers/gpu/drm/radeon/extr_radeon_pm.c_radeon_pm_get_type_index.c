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
struct TYPE_4__ {int num_power_states; int default_power_state_index; TYPE_1__* power_state; } ;
struct radeon_device {TYPE_2__ pm; } ;
typedef  enum radeon_pm_state_type { ____Placeholder_radeon_pm_state_type } radeon_pm_state_type ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */

int radeon_pm_get_type_index(struct radeon_device *rdev,
			     enum radeon_pm_state_type ps_type,
			     int instance)
{
	int i;
	int found_instance = -1;

	for (i = 0; i < rdev->pm.num_power_states; i++) {
		if (rdev->pm.power_state[i].type == ps_type) {
			found_instance++;
			if (found_instance == instance)
				return i;
		}
	}
	/* return default if no match */
	return rdev->pm.default_power_state_index;
}