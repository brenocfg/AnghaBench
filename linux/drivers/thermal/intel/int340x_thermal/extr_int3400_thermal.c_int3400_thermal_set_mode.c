#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {struct int3400_thermal_priv* devdata; } ;
struct int3400_thermal_priv {int mode; int /*<<< orphan*/  current_uuid_index; TYPE_1__* adev; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int THERMAL_DEVICE_DISABLED ; 
 int THERMAL_DEVICE_ENABLED ; 
 int int3400_thermal_run_osc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int int3400_thermal_set_mode(struct thermal_zone_device *thermal,
				enum thermal_device_mode mode)
{
	struct int3400_thermal_priv *priv = thermal->devdata;
	bool enable;
	int result = 0;

	if (!priv)
		return -EINVAL;

	if (mode == THERMAL_DEVICE_ENABLED)
		enable = true;
	else if (mode == THERMAL_DEVICE_DISABLED)
		enable = false;
	else
		return -EINVAL;

	if (enable != priv->mode) {
		priv->mode = enable;
		result = int3400_thermal_run_osc(priv->adev->handle,
						 priv->current_uuid_index,
						 enable);
	}
	return result;
}