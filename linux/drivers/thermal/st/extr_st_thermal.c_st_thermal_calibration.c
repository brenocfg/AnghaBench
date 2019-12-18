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
struct st_thermal_sensor {TYPE_1__* cdata; int /*<<< orphan*/  dcorrect; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  calibration_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_thermal_calibration(struct st_thermal_sensor *sensor)
{
	int ret;
	unsigned int val;
	struct device *dev = sensor->dev;

	/* Check if sensor calibration data is already written */
	ret = regmap_field_read(sensor->dcorrect, &val);
	if (ret) {
		dev_err(dev, "failed to read calibration data\n");
		return ret;
	}

	if (!val) {
		/*
		 * Sensor calibration value not set by bootloader,
		 * default calibration data to be used
		 */
		ret = regmap_field_write(sensor->dcorrect,
					 sensor->cdata->calibration_val);
		if (ret)
			dev_err(dev, "failed to set calibration data\n");
	}

	return ret;
}