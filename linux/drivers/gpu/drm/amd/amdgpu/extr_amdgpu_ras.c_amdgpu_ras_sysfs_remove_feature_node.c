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
struct bin_attribute {int dummy; } ;
struct attribute_group {char* name; struct bin_attribute** bin_attrs; struct attribute** attrs; } ;
struct attribute {int dummy; } ;
struct TYPE_3__ {struct attribute attr; } ;
struct amdgpu_ras {struct bin_attribute badpages_attr; TYPE_1__ features_attr; } ;
struct amdgpu_device {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,struct attribute_group*) ; 

__attribute__((used)) static int amdgpu_ras_sysfs_remove_feature_node(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	struct attribute *attrs[] = {
		&con->features_attr.attr,
		NULL
	};
	struct bin_attribute *bin_attrs[] = {
		&con->badpages_attr,
		NULL
	};
	struct attribute_group group = {
		.name = "ras",
		.attrs = attrs,
		.bin_attrs = bin_attrs,
	};

	sysfs_remove_group(&adev->dev->kobj, &group);

	return 0;
}