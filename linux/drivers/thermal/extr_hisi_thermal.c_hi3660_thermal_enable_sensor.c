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
struct hisi_thermal_sensor {int /*<<< orphan*/  id; int /*<<< orphan*/  thres_temp; struct hisi_thermal_data* data; } ;
struct hisi_thermal_data {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HI3660_TEMP_LAG ; 
 int /*<<< orphan*/  hi3660_thermal_alarm_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi3660_thermal_alarm_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi3660_thermal_alarm_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hi3660_thermal_set_lag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int hi3660_thermal_temp_to_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi3660_thermal_enable_sensor(struct hisi_thermal_sensor *sensor)
{
	unsigned int value;
	struct hisi_thermal_data *data = sensor->data;

	/* disable interrupt */
	hi3660_thermal_alarm_enable(data->regs, sensor->id, 0);

	/* setting lag value between current temp and the threshold */
	hi3660_thermal_set_lag(data->regs, sensor->id, HI3660_TEMP_LAG);

	/* set interrupt threshold */
	value = hi3660_thermal_temp_to_step(sensor->thres_temp);
	hi3660_thermal_alarm_set(data->regs, sensor->id, value);

	/* enable interrupt */
	hi3660_thermal_alarm_clear(data->regs, sensor->id, 1);
	hi3660_thermal_alarm_enable(data->regs, sensor->id, 1);

	return 0;
}