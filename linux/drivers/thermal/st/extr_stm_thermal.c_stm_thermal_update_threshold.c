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
struct stm_thermal_sensor {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  THERMAL_DEVICE_DISABLED ; 
 int /*<<< orphan*/  THERMAL_DEVICE_ENABLED ; 
 int stm_disable_irq (struct stm_thermal_sensor*) ; 
 int stm_enable_irq (struct stm_thermal_sensor*) ; 
 int stm_sensor_power_off (struct stm_thermal_sensor*) ; 
 int stm_sensor_power_on (struct stm_thermal_sensor*) ; 
 int stm_thermal_set_threshold (struct stm_thermal_sensor*) ; 

__attribute__((used)) static int stm_thermal_update_threshold(struct stm_thermal_sensor *sensor)
{
	int ret;

	sensor->mode = THERMAL_DEVICE_DISABLED;

	ret = stm_sensor_power_off(sensor);
	if (ret)
		return ret;

	ret = stm_disable_irq(sensor);
	if (ret)
		return ret;

	ret = stm_thermal_set_threshold(sensor);
	if (ret)
		return ret;

	ret = stm_enable_irq(sensor);
	if (ret)
		return ret;

	ret = stm_sensor_power_on(sensor);
	if (ret)
		return ret;

	sensor->mode = THERMAL_DEVICE_ENABLED;

	return 0;
}