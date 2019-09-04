#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct k8temp_data {int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct k8temp_data* pci_get_drvdata (struct pci_dev*) ; 
 TYPE_4__ sensor_dev_attr_temp1_input ; 
 TYPE_3__ sensor_dev_attr_temp2_input ; 
 TYPE_2__ sensor_dev_attr_temp3_input ; 
 TYPE_1__ sensor_dev_attr_temp4_input ; 

__attribute__((used)) static void k8temp_remove(struct pci_dev *pdev)
{
	struct k8temp_data *data = pci_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp1_input.dev_attr);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp2_input.dev_attr);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp3_input.dev_attr);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp4_input.dev_attr);
	device_remove_file(&pdev->dev, &dev_attr_name);
}