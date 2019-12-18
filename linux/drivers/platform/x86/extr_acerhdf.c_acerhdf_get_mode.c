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
 int THERMAL_DEVICE_DISABLED ; 
 int THERMAL_DEVICE_ENABLED ; 
 scalar_t__ kernelmode ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int acerhdf_get_mode(struct thermal_zone_device *thermal,
			    enum thermal_device_mode *mode)
{
	if (verbose)
		pr_notice("kernel mode fan control %d\n", kernelmode);

	*mode = (kernelmode) ? THERMAL_DEVICE_ENABLED
			     : THERMAL_DEVICE_DISABLED;

	return 0;
}