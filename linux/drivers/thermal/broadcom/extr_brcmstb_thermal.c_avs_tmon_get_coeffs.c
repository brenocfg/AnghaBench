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

/* Variables and functions */
 int thermal_zone_get_offset (struct thermal_zone_device*) ; 
 int thermal_zone_get_slope (struct thermal_zone_device*) ; 

__attribute__((used)) static void avs_tmon_get_coeffs(struct thermal_zone_device *tz, int *slope,
				int *offset)
{
	*slope = thermal_zone_get_slope(tz);
	*offset = thermal_zone_get_offset(tz);
}