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
typedef  int /*<<< orphan*/  u32 ;
struct ina3221_data {TYPE_1__* inputs; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;
struct TYPE_2__ {char* label; } ;

/* Variables and functions */
 struct ina3221_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int ina3221_read_string(struct device *dev, enum hwmon_sensor_types type,
			       u32 attr, int channel, const char **str)
{
	struct ina3221_data *ina = dev_get_drvdata(dev);
	int index = channel - 1;

	*str = ina->inputs[index].label;

	return 0;
}