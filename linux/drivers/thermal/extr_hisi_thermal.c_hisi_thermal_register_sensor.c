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
struct thermal_trip {scalar_t__ type; int /*<<< orphan*/  temperature; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hisi_thermal_sensor {int /*<<< orphan*/  thres_temp; int /*<<< orphan*/ * tzd; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ THERMAL_TRIP_PASSIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * devm_thermal_zone_of_sensor_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hisi_thermal_sensor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_of_thermal_ops ; 
 int of_thermal_get_ntrips (int /*<<< orphan*/ *) ; 
 struct thermal_trip* of_thermal_get_trip_points (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_thermal_register_sensor(struct platform_device *pdev,
					struct hisi_thermal_sensor *sensor)
{
	int ret, i;
	const struct thermal_trip *trip;

	sensor->tzd = devm_thermal_zone_of_sensor_register(&pdev->dev,
							   sensor->id, sensor,
							   &hisi_of_thermal_ops);
	if (IS_ERR(sensor->tzd)) {
		ret = PTR_ERR(sensor->tzd);
		sensor->tzd = NULL;
		dev_err(&pdev->dev, "failed to register sensor id %d: %d\n",
			sensor->id, ret);
		return ret;
	}

	trip = of_thermal_get_trip_points(sensor->tzd);

	for (i = 0; i < of_thermal_get_ntrips(sensor->tzd); i++) {
		if (trip[i].type == THERMAL_TRIP_PASSIVE) {
			sensor->thres_temp = trip[i].temperature;
			break;
		}
	}

	return 0;
}