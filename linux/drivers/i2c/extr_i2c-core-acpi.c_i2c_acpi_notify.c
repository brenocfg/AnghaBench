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
struct notifier_block {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct i2c_board_info {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  ACPI_RECONFIG_DEVICE_ADD 129 
#define  ACPI_RECONFIG_DEVICE_REMOVE 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  acpi_device_enumerated (struct acpi_device*) ; 
 struct i2c_adapter* i2c_acpi_find_adapter_by_handle (int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_acpi_find_client_by_adev (struct acpi_device*) ; 
 int /*<<< orphan*/  i2c_acpi_get_info (struct acpi_device*,struct i2c_board_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_acpi_register_device (struct i2c_adapter*,struct acpi_device*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_acpi_notify(struct notifier_block *nb, unsigned long value,
			   void *arg)
{
	struct acpi_device *adev = arg;
	struct i2c_board_info info;
	acpi_handle adapter_handle;
	struct i2c_adapter *adapter;
	struct i2c_client *client;

	switch (value) {
	case ACPI_RECONFIG_DEVICE_ADD:
		if (i2c_acpi_get_info(adev, &info, NULL, &adapter_handle))
			break;

		adapter = i2c_acpi_find_adapter_by_handle(adapter_handle);
		if (!adapter)
			break;

		i2c_acpi_register_device(adapter, adev, &info);
		break;
	case ACPI_RECONFIG_DEVICE_REMOVE:
		if (!acpi_device_enumerated(adev))
			break;

		client = i2c_acpi_find_client_by_adev(adev);
		if (!client)
			break;

		i2c_unregister_device(client);
		put_device(&client->dev);
		break;
	}

	return NOTIFY_OK;
}