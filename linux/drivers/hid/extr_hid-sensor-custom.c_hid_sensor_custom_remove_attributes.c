#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hid_sensor_custom {int sensor_field_count; TYPE_3__* fields; TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  hid_custom_attribute_group; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hid_sensor_custom_remove_attributes(struct hid_sensor_custom *
								sensor_inst)
{
	int i;

	for (i = 0; i < sensor_inst->sensor_field_count; ++i)
		sysfs_remove_group(&sensor_inst->pdev->dev.kobj,
				   &sensor_inst->fields[i].
				   hid_custom_attribute_group);

	kfree(sensor_inst->fields);
}