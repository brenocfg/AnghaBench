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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hisi_thermal_data {int nr_sensors; TYPE_1__* sensor; struct platform_device* pdev; } ;
struct TYPE_2__ {char* irq_name; struct hisi_thermal_data* data; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HI3660_BIG_SENSOR ; 
 int /*<<< orphan*/  HI3660_LITTLE_SENSOR ; 
 TYPE_1__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi3660_thermal_probe(struct hisi_thermal_data *data)
{
	struct platform_device *pdev = data->pdev;
	struct device *dev = &pdev->dev;

	data->nr_sensors = 1;

	data->sensor = devm_kzalloc(dev, sizeof(*data->sensor) *
				    data->nr_sensors, GFP_KERNEL);
	if (!data->sensor)
		return -ENOMEM;

	data->sensor[0].id = HI3660_BIG_SENSOR;
	data->sensor[0].irq_name = "tsensor_a73";
	data->sensor[0].data = data;

	data->sensor[1].id = HI3660_LITTLE_SENSOR;
	data->sensor[1].irq_name = "tsensor_a53";
	data->sensor[1].data = data;

	return 0;
}