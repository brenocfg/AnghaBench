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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct scmi_sensors {struct scmi_sensor_info*** info; } ;
struct scmi_sensor_info {scalar_t__ name; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 

__attribute__((used)) static umode_t
scmi_hwmon_is_visible(const void *drvdata, enum hwmon_sensor_types type,
		      u32 attr, int channel)
{
	const struct scmi_sensor_info *sensor;
	const struct scmi_sensors *scmi_sensors = drvdata;

	sensor = *(scmi_sensors->info[type] + channel);
	if (sensor && sensor->name)
		return S_IRUGO;

	return 0;
}