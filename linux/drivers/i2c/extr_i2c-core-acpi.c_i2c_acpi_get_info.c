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
struct i2c_board_info {int /*<<< orphan*/  type; int /*<<< orphan*/  fwnode; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct i2c_acpi_lookup {int index; scalar_t__ adapter_handle; struct i2c_board_info* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  present; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ status; } ;
typedef  int /*<<< orphan*/  lookup ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ acpi_bus_get_device (scalar_t__,struct acpi_device**) ; 
 scalar_t__ acpi_bus_get_status (struct acpi_device*) ; 
 scalar_t__ acpi_device_enumerated (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_fwnode_handle (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_set_modalias (struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int i2c_acpi_do_lookup (struct acpi_device*,struct i2c_acpi_lookup*) ; 
 int /*<<< orphan*/  memset (struct i2c_acpi_lookup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_acpi_get_info(struct acpi_device *adev,
			     struct i2c_board_info *info,
			     struct i2c_adapter *adapter,
			     acpi_handle *adapter_handle)
{
	struct i2c_acpi_lookup lookup;
	int ret;

	memset(&lookup, 0, sizeof(lookup));
	lookup.info = info;
	lookup.index = -1;

	if (acpi_device_enumerated(adev))
		return -EINVAL;

	ret = i2c_acpi_do_lookup(adev, &lookup);
	if (ret)
		return ret;

	if (adapter) {
		/* The adapter must match the one in I2cSerialBus() connector */
		if (ACPI_HANDLE(&adapter->dev) != lookup.adapter_handle)
			return -ENODEV;
	} else {
		struct acpi_device *adapter_adev;

		/* The adapter must be present */
		if (acpi_bus_get_device(lookup.adapter_handle, &adapter_adev))
			return -ENODEV;
		if (acpi_bus_get_status(adapter_adev) ||
		    !adapter_adev->status.present)
			return -ENODEV;
	}

	info->fwnode = acpi_fwnode_handle(adev);
	if (adapter_handle)
		*adapter_handle = lookup.adapter_handle;

	acpi_set_modalias(adev, dev_name(&adev->dev), info->type,
			  sizeof(info->type));

	return 0;
}