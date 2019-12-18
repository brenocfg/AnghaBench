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
struct stm_thermal_sensor {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int stm_sensor_power_off (struct stm_thermal_sensor*) ; 

__attribute__((used)) static int stm_thermal_sensor_off(struct stm_thermal_sensor *sensor)
{
	int ret;

	ret = stm_sensor_power_off(sensor);
	if (ret)
		return ret;

	clk_disable_unprepare(sensor->clk);

	return 0;
}