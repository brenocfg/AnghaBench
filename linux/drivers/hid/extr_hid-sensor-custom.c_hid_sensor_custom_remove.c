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
struct TYPE_4__ {struct hid_sensor_hub_device* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hid_sensor_hub_device {int /*<<< orphan*/  usage; } ;
struct hid_sensor_custom {TYPE_3__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_sensor_attr_group ; 
 int /*<<< orphan*/  hid_sensor_custom_dev_if_remove (struct hid_sensor_custom*) ; 
 int /*<<< orphan*/  hid_sensor_custom_remove_attributes (struct hid_sensor_custom*) ; 
 struct hid_sensor_custom* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sensor_hub_remove_callback (struct hid_sensor_hub_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hid_sensor_custom_remove(struct platform_device *pdev)
{
	struct hid_sensor_custom *sensor_inst = platform_get_drvdata(pdev);
	struct hid_sensor_hub_device *hsdev = pdev->dev.platform_data;

	hid_sensor_custom_dev_if_remove(sensor_inst);
	hid_sensor_custom_remove_attributes(sensor_inst);
	sysfs_remove_group(&sensor_inst->pdev->dev.kobj,
			   &enable_sensor_attr_group);
	sensor_hub_remove_callback(hsdev, hsdev->usage);

	return 0;
}