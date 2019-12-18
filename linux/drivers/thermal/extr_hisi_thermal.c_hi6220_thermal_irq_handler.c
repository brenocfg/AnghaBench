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
struct hisi_thermal_sensor {struct hisi_thermal_data* data; } ;
struct hisi_thermal_data {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  hi6220_thermal_alarm_clear (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hi6220_thermal_irq_handler(struct hisi_thermal_sensor *sensor)
{
	struct hisi_thermal_data *data = sensor->data;

	hi6220_thermal_alarm_clear(data->regs, 1);
	return 0;
}