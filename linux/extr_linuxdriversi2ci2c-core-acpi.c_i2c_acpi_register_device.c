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
struct i2c_board_info {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int ignore_parent; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_2__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_device_set_enumerated (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 

__attribute__((used)) static void i2c_acpi_register_device(struct i2c_adapter *adapter,
				     struct acpi_device *adev,
				     struct i2c_board_info *info)
{
	adev->power.flags.ignore_parent = true;
	acpi_device_set_enumerated(adev);

	if (!i2c_new_device(adapter, info)) {
		adev->power.flags.ignore_parent = false;
		dev_err(&adapter->dev,
			"failed to add I2C device %s from ACPI\n",
			dev_name(&adev->dev));
	}
}