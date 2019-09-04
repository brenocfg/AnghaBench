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
struct thermal_zone_device {struct mlxsw_thermal* devdata; } ;
struct mlxsw_thermal {int mode; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */

__attribute__((used)) static int mlxsw_thermal_get_mode(struct thermal_zone_device *tzdev,
				  enum thermal_device_mode *mode)
{
	struct mlxsw_thermal *thermal = tzdev->devdata;

	*mode = thermal->mode;

	return 0;
}