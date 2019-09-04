#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ibmpex_bmc_data {int num_sensors; struct ibmpex_bmc_data* sensors; int /*<<< orphan*/  user; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  bmc_device; int /*<<< orphan*/  list; TYPE_2__* attr; } ;
struct TYPE_6__ {struct ibmpex_bmc_data* name; } ;
struct TYPE_10__ {TYPE_1__ attr; } ;
struct TYPE_9__ {TYPE_5__ dev_attr; } ;
struct TYPE_8__ {TYPE_5__ dev_attr; } ;
struct TYPE_7__ {TYPE_5__ dev_attr; } ;

/* Variables and functions */
 int PEX_NUM_SENSOR_FUNCS ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ibmpex_bmc_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_4__ sensor_dev_attr_name ; 
 TYPE_3__ sensor_dev_attr_reset_high_low ; 

__attribute__((used)) static void ibmpex_bmc_delete(struct ibmpex_bmc_data *data)
{
	int i, j;

	device_remove_file(data->bmc_device,
			   &sensor_dev_attr_reset_high_low.dev_attr);
	device_remove_file(data->bmc_device, &sensor_dev_attr_name.dev_attr);
	for (i = 0; i < data->num_sensors; i++)
		for (j = 0; j < PEX_NUM_SENSOR_FUNCS; j++) {
			if (!data->sensors[i].attr[j].dev_attr.attr.name)
				continue;
			device_remove_file(data->bmc_device,
				&data->sensors[i].attr[j].dev_attr);
			kfree(data->sensors[i].attr[j].dev_attr.attr.name);
		}

	list_del(&data->list);
	dev_set_drvdata(data->bmc_device, NULL);
	hwmon_device_unregister(data->hwmon_dev);
	ipmi_destroy_user(data->user);
	kfree(data->sensors);
	kfree(data);
}