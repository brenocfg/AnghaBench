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
struct i2c_client {int dummy; } ;
struct i2c_board_info {int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct i2c_acpi_lookup {int index; int /*<<< orphan*/  adapter_handle; int /*<<< orphan*/  device_handle; struct i2c_board_info* info; } ;
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 struct i2c_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (int /*<<< orphan*/ *) ; 
 int acpi_dev_get_resources (struct acpi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i2c_acpi_lookup*) ; 
 int /*<<< orphan*/  acpi_device_handle (struct acpi_device*) ; 
 int /*<<< orphan*/  i2c_acpi_fill_info ; 
 struct i2c_adapter* i2c_acpi_find_adapter_by_handle (int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  memset (struct i2c_acpi_lookup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list ; 

struct i2c_client *i2c_acpi_new_device(struct device *dev, int index,
				       struct i2c_board_info *info)
{
	struct i2c_acpi_lookup lookup;
	struct i2c_adapter *adapter;
	struct i2c_client *client;
	struct acpi_device *adev;
	LIST_HEAD(resource_list);
	int ret;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		return ERR_PTR(-EINVAL);

	memset(&lookup, 0, sizeof(lookup));
	lookup.info = info;
	lookup.device_handle = acpi_device_handle(adev);
	lookup.index = index;

	ret = acpi_dev_get_resources(adev, &resource_list,
				     i2c_acpi_fill_info, &lookup);
	if (ret < 0)
		return ERR_PTR(ret);

	acpi_dev_free_resource_list(&resource_list);

	if (!info->addr)
		return ERR_PTR(-EADDRNOTAVAIL);

	adapter = i2c_acpi_find_adapter_by_handle(lookup.adapter_handle);
	if (!adapter)
		return ERR_PTR(-EPROBE_DEFER);

	client = i2c_new_device(adapter, info);
	if (!client)
		return ERR_PTR(-ENODEV);

	return client;
}