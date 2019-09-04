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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int cpuidle_enter_state (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 int cpuidle_enter_state_coupled (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 scalar_t__ cpuidle_state_is_coupled (struct cpuidle_driver*,int) ; 

int cpuidle_enter(struct cpuidle_driver *drv, struct cpuidle_device *dev,
		  int index)
{
	if (cpuidle_state_is_coupled(drv, index))
		return cpuidle_enter_state_coupled(dev, drv, index);
	return cpuidle_enter_state(dev, drv, index);
}