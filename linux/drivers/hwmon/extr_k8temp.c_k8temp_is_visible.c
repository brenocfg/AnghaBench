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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct k8temp_data {int sensorsp; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int SEL_CORE ; 
 int SEL_PLACE ; 

__attribute__((used)) static umode_t
k8temp_is_visible(const void *drvdata, enum hwmon_sensor_types type,
		  u32 attr, int channel)
{
	const struct k8temp_data *data = drvdata;

	if ((channel & 1) && !(data->sensorsp & SEL_PLACE))
		return 0;

	if ((channel & 2) && !(data->sensorsp & SEL_CORE))
		return 0;

	return 0444;
}