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
struct thermal_zone_device {struct imx_thermal_data* devdata; } ;
struct imx_thermal_data {int temp_critical; int temp_passive; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int IMX_TRIP_CRITICAL ; 
 int /*<<< orphan*/  imx_set_alarm_temp (struct imx_thermal_data*,int) ; 

__attribute__((used)) static int imx_set_trip_temp(struct thermal_zone_device *tz, int trip,
			     int temp)
{
	struct imx_thermal_data *data = tz->devdata;

	/* do not allow changing critical threshold */
	if (trip == IMX_TRIP_CRITICAL)
		return -EPERM;

	/* do not allow passive to be set higher than critical */
	if (temp < 0 || temp > data->temp_critical)
		return -EINVAL;

	data->temp_passive = temp;

	imx_set_alarm_temp(data, temp);

	return 0;
}