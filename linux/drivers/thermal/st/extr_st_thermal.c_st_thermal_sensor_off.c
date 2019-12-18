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
struct st_thermal_sensor {int /*<<< orphan*/  clk; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* power_ctrl ) (struct st_thermal_sensor*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_OFF ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int stub1 (struct st_thermal_sensor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_thermal_sensor_off(struct st_thermal_sensor *sensor)
{
	int ret;

	ret = sensor->ops->power_ctrl(sensor, POWER_OFF);
	if (ret)
		return ret;

	clk_disable_unprepare(sensor->clk);

	return 0;
}