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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  sensor_id; } ;
struct sensor_data {TYPE_1__ info; } ;
struct scpi_thermal_zone {size_t sensor_id; struct scpi_sensors* scpi_sensors; } ;
struct scpi_sensors {struct sensor_data* data; struct scpi_ops* scpi_ops; } ;
struct scpi_ops {int (* sensor_get_value ) (int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  scpi_scale_reading (int*,struct sensor_data*) ; 
 int stub1 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int scpi_read_temp(void *dev, int *temp)
{
	struct scpi_thermal_zone *zone = dev;
	struct scpi_sensors *scpi_sensors = zone->scpi_sensors;
	struct scpi_ops *scpi_ops = scpi_sensors->scpi_ops;
	struct sensor_data *sensor = &scpi_sensors->data[zone->sensor_id];
	u64 value;
	int ret;

	ret = scpi_ops->sensor_get_value(sensor->info.sensor_id, &value);
	if (ret)
		return ret;

	scpi_scale_reading(&value, sensor);

	*temp = value;
	return 0;
}