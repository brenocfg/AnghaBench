#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i2c_board_info {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 scalar_t__ i2c_acpi_get_info (struct acpi_device*,struct i2c_board_info*,struct i2c_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_acpi_register_device (struct i2c_adapter*,struct acpi_device*,struct i2c_board_info*) ; 

__attribute__((used)) static acpi_status i2c_acpi_add_device(acpi_handle handle, u32 level,
				       void *data, void **return_value)
{
	struct i2c_adapter *adapter = data;
	struct acpi_device *adev;
	struct i2c_board_info info;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;

	if (i2c_acpi_get_info(adev, &info, adapter, NULL))
		return AE_OK;

	i2c_acpi_register_device(adapter, adev, &info);

	return AE_OK;
}