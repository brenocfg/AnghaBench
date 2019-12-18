#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hisi_thermal_sensor {int thres_temp; int /*<<< orphan*/  id; int /*<<< orphan*/  tzd; struct hisi_thermal_data* data; } ;
struct hisi_thermal_data {TYPE_2__* pdev; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_handler ) (struct hisi_thermal_sensor*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hisi_thermal_get_temp (struct hisi_thermal_sensor*,int*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_thermal_sensor*) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hisi_thermal_alarm_irq_thread(int irq, void *dev)
{
	struct hisi_thermal_sensor *sensor = dev;
	struct hisi_thermal_data *data = sensor->data;
	int temp = 0;

	data->ops->irq_handler(sensor);

	hisi_thermal_get_temp(sensor, &temp);

	if (temp >= sensor->thres_temp) {
		dev_crit(&data->pdev->dev,
			 "sensor <%d> THERMAL ALARM: %d > %d\n",
			 sensor->id, temp, sensor->thres_temp);

		thermal_zone_device_update(sensor->tzd,
					   THERMAL_EVENT_UNSPECIFIED);

	} else {
		dev_crit(&data->pdev->dev,
			 "sensor <%d> THERMAL ALARM stopped: %d < %d\n",
			 sensor->id, temp, sensor->thres_temp);
	}

	return IRQ_HANDLED;
}