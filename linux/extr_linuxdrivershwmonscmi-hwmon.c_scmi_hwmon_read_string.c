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
typedef  int /*<<< orphan*/  u32 ;
struct scmi_sensors {struct scmi_sensor_info*** info; } ;
struct scmi_sensor_info {char* name; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 struct scmi_sensors* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int
scmi_hwmon_read_string(struct device *dev, enum hwmon_sensor_types type,
		       u32 attr, int channel, const char **str)
{
	const struct scmi_sensor_info *sensor;
	struct scmi_sensors *scmi_sensors = dev_get_drvdata(dev);

	sensor = *(scmi_sensors->info[type] + channel);
	*str = sensor->name;

	return 0;
}