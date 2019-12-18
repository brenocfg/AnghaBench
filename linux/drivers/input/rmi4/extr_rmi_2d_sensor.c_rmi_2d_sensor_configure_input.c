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
struct rmi_function {struct rmi_device* rmi_dev; } ;
struct rmi_driver_data {scalar_t__ input; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct rmi_2d_sensor {scalar_t__ input; } ;

/* Variables and functions */
 int ENODEV ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmi_2d_sensor_set_input_params (struct rmi_2d_sensor*) ; 

int rmi_2d_sensor_configure_input(struct rmi_function *fn,
					struct rmi_2d_sensor *sensor)
{
	struct rmi_device *rmi_dev = fn->rmi_dev;
	struct rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);

	if (!drv_data->input)
		return -ENODEV;

	sensor->input = drv_data->input;
	rmi_2d_sensor_set_input_params(sensor);

	return 0;
}