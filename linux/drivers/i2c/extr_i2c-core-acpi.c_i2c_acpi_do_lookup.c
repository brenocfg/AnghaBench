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
struct list_head {int dummy; } ;
struct i2c_board_info {int /*<<< orphan*/  addr; } ;
struct i2c_acpi_lookup {int /*<<< orphan*/  device_handle; struct i2c_board_info* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  present; } ;
struct acpi_device {TYPE_1__ status; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ acpi_bus_get_status (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (struct list_head*) ; 
 int acpi_dev_get_resources (struct acpi_device*,struct list_head*,int /*<<< orphan*/ ,struct i2c_acpi_lookup*) ; 
 int /*<<< orphan*/  acpi_device_handle (struct acpi_device*) ; 
 scalar_t__ acpi_match_device_ids (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_acpi_fill_info ; 
 int /*<<< orphan*/  i2c_acpi_ignored_device_ids ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_acpi_do_lookup(struct acpi_device *adev,
			      struct i2c_acpi_lookup *lookup)
{
	struct i2c_board_info *info = lookup->info;
	struct list_head resource_list;
	int ret;

	if (acpi_bus_get_status(adev) || !adev->status.present)
		return -EINVAL;

	if (acpi_match_device_ids(adev, i2c_acpi_ignored_device_ids) == 0)
		return -ENODEV;

	memset(info, 0, sizeof(*info));
	lookup->device_handle = acpi_device_handle(adev);

	/* Look up for I2cSerialBus resource */
	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     i2c_acpi_fill_info, lookup);
	acpi_dev_free_resource_list(&resource_list);

	if (ret < 0 || !info->addr)
		return -EINVAL;

	return 0;
}