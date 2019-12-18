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
struct hisi_thermal_sensor {int /*<<< orphan*/  thres_temp; int /*<<< orphan*/  id; int /*<<< orphan*/  tzd; struct hisi_thermal_data* data; } ;
struct hisi_thermal_data {TYPE_2__* pdev; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* get_temp ) (struct hisi_thermal_sensor*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct hisi_thermal_sensor*) ; 

__attribute__((used)) static int hisi_thermal_get_temp(void *__data, int *temp)
{
	struct hisi_thermal_sensor *sensor = __data;
	struct hisi_thermal_data *data = sensor->data;

	*temp = data->ops->get_temp(sensor);

	dev_dbg(&data->pdev->dev, "tzd=%p, id=%d, temp=%d, thres=%d\n",
		sensor->tzd, sensor->id, *temp, sensor->thres_temp);

	return 0;
}