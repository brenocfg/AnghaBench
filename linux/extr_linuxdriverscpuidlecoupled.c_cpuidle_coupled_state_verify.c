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
struct cpuidle_driver {int state_count; int safe_state_index; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cpuidle_state_is_coupled (struct cpuidle_driver*,int) ; 

int cpuidle_coupled_state_verify(struct cpuidle_driver *drv)
{
	int i;

	for (i = drv->state_count - 1; i >= 0; i--) {
		if (cpuidle_state_is_coupled(drv, i) &&
		    (drv->safe_state_index == i ||
		     drv->safe_state_index < 0 ||
		     drv->safe_state_index >= drv->state_count))
			return -EINVAL;
	}

	return 0;
}