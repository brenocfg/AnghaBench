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
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 unsigned long MLXSW_THERMAL_MAX_STATE ; 

__attribute__((used)) static int mlxsw_thermal_get_max_state(struct thermal_cooling_device *cdev,
				       unsigned long *p_state)
{
	*p_state = MLXSW_THERMAL_MAX_STATE;
	return 0;
}