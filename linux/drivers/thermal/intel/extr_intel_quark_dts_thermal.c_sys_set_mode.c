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
struct thermal_zone_device {int dummy; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */
 int THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  dts_update_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int soc_dts_disable (struct thermal_zone_device*) ; 
 int soc_dts_enable (struct thermal_zone_device*) ; 

__attribute__((used)) static int sys_set_mode(struct thermal_zone_device *tzd,
				enum thermal_device_mode mode)
{
	int ret;

	mutex_lock(&dts_update_mutex);
	if (mode == THERMAL_DEVICE_ENABLED)
		ret = soc_dts_enable(tzd);
	else
		ret = soc_dts_disable(tzd);
	mutex_unlock(&dts_update_mutex);

	return ret;
}