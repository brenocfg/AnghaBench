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
struct ti_thermal_data {int /*<<< orphan*/  polling_delay; struct ti_thermal_data* ti_thermal; int /*<<< orphan*/  sensor_id; } ;
struct ti_bandgap {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct ti_thermal_data*) ; 
 int PTR_ERR (struct ti_thermal_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ti_thermal_data* devm_thermal_zone_of_sensor_register (int /*<<< orphan*/ ,int,struct ti_thermal_data*,int /*<<< orphan*/ *) ; 
 struct ti_thermal_data* ti_bandgap_get_sensor_data (struct ti_bandgap*,int) ; 
 int /*<<< orphan*/  ti_bandgap_set_sensor_data (struct ti_bandgap*,int,struct ti_thermal_data*) ; 
 int /*<<< orphan*/  ti_bandgap_write_update_interval (struct ti_bandgap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_of_thermal_ops ; 
 struct ti_thermal_data* ti_thermal_build_data (struct ti_bandgap*,int) ; 

int ti_thermal_expose_sensor(struct ti_bandgap *bgp, int id,
			     char *domain)
{
	struct ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	if (!data || IS_ERR(data))
		data = ti_thermal_build_data(bgp, id);

	if (!data)
		return -EINVAL;

	/* in case this is specified by DT */
	data->ti_thermal = devm_thermal_zone_of_sensor_register(bgp->dev, id,
					data, &ti_of_thermal_ops);
	if (IS_ERR(data->ti_thermal)) {
		dev_err(bgp->dev, "thermal zone device is NULL\n");
		return PTR_ERR(data->ti_thermal);
	}

	ti_bandgap_set_sensor_data(bgp, id, data);
	ti_bandgap_write_update_interval(bgp, data->sensor_id,
					data->ti_thermal->polling_delay);

	return 0;
}