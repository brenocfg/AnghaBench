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
struct TYPE_3__ {int /*<<< orphan*/  max_power_default; } ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_2__* asic_funcs; TYPE_1__ asic_prop; int /*<<< orphan*/  max_power; int /*<<< orphan*/  pm_mng_profile; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* add_device_attr ) (struct hl_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PM_AUTO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int device_add_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_dev_attr_groups ; 
 int /*<<< orphan*/  hl_dev_clks_attr_group ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ *) ; 

int hl_sysfs_init(struct hl_device *hdev)
{
	int rc;

	hdev->pm_mng_profile = PM_AUTO;
	hdev->max_power = hdev->asic_prop.max_power_default;

	hdev->asic_funcs->add_device_attr(hdev, &hl_dev_clks_attr_group);

	rc = device_add_groups(hdev->dev, hl_dev_attr_groups);
	if (rc) {
		dev_err(hdev->dev,
			"Failed to add groups to device, error %d\n", rc);
		return rc;
	}

	return 0;
}