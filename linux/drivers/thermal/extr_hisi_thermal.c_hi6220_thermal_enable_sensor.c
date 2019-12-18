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
struct hisi_thermal_sensor {int /*<<< orphan*/  thres_temp; int /*<<< orphan*/  id; struct hisi_thermal_data* data; } ;
struct hisi_thermal_data {int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  HI6220_TEMP_LAG ; 
 int /*<<< orphan*/  HI6220_TEMP_RESET ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_thermal_alarm_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_thermal_alarm_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi6220_thermal_alarm_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_thermal_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi6220_thermal_hdak_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_thermal_reset_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi6220_thermal_reset_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_thermal_sensor_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_thermal_set_lag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6220_thermal_enable_sensor(struct hisi_thermal_sensor *sensor)
{
	struct hisi_thermal_data *data = sensor->data;
	int ret;

	/* enable clock for tsensor */
	ret = clk_prepare_enable(data->clk);
	if (ret)
		return ret;

	/* disable module firstly */
	hi6220_thermal_reset_enable(data->regs, 0);
	hi6220_thermal_enable(data->regs, 0);

	/* select sensor id */
	hi6220_thermal_sensor_select(data->regs, sensor->id);

	/* setting the hdak time */
	hi6220_thermal_hdak_set(data->regs, 0);

	/* setting lag value between current temp and the threshold */
	hi6220_thermal_set_lag(data->regs, HI6220_TEMP_LAG);

	/* enable for interrupt */
	hi6220_thermal_alarm_set(data->regs, sensor->thres_temp);

	hi6220_thermal_reset_set(data->regs, HI6220_TEMP_RESET);

	/* enable module */
	hi6220_thermal_reset_enable(data->regs, 1);
	hi6220_thermal_enable(data->regs, 1);

	hi6220_thermal_alarm_clear(data->regs, 0);
	hi6220_thermal_alarm_enable(data->regs, 1);

	return 0;
}