#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_hive_info {int number_devices; int /*<<< orphan*/ * kobj; struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_2__* dev; TYPE_1__* ddev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  unique; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_xgmi_device_id ; 
 int /*<<< orphan*/  dev_attr_xgmi_error ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_xgmi_sysfs_add_dev_info(struct amdgpu_device *adev,
					 struct amdgpu_hive_info *hive)
{
	int ret = 0;
	char node[10] = { 0 };

	/* Create xgmi device id file */
	ret = device_create_file(adev->dev, &dev_attr_xgmi_device_id);
	if (ret) {
		dev_err(adev->dev, "XGMI: Failed to create device file xgmi_device_id\n");
		return ret;
	}

	/* Create xgmi error file */
	ret = device_create_file(adev->dev, &dev_attr_xgmi_error);
	if (ret)
		pr_err("failed to create xgmi_error\n");


	/* Create sysfs link to hive info folder on the first device */
	if (adev != hive->adev) {
		ret = sysfs_create_link(&adev->dev->kobj, hive->kobj,
					"xgmi_hive_info");
		if (ret) {
			dev_err(adev->dev, "XGMI: Failed to create link to hive info");
			goto remove_file;
		}
	}

	sprintf(node, "node%d", hive->number_devices);
	/* Create sysfs link form the hive folder to yourself */
	ret = sysfs_create_link(hive->kobj, &adev->dev->kobj, node);
	if (ret) {
		dev_err(adev->dev, "XGMI: Failed to create link from hive info");
		goto remove_link;
	}

	goto success;


remove_link:
	sysfs_remove_link(&adev->dev->kobj, adev->ddev->unique);

remove_file:
	device_remove_file(adev->dev, &dev_attr_xgmi_device_id);

success:
	return ret;
}