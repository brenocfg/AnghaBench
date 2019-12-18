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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct i2c_board_info {scalar_t__ dev_name; } ;
struct i2c_adapter {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_dev_name (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  i2c_adapter_id (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_encode_flags_to_addr (struct i2c_client*) ; 

__attribute__((used)) static void i2c_dev_set_name(struct i2c_adapter *adap,
			     struct i2c_client *client,
			     struct i2c_board_info const *info)
{
	struct acpi_device *adev = ACPI_COMPANION(&client->dev);

	if (info && info->dev_name) {
		dev_set_name(&client->dev, "i2c-%s", info->dev_name);
		return;
	}

	if (adev) {
		dev_set_name(&client->dev, "i2c-%s", acpi_dev_name(adev));
		return;
	}

	dev_set_name(&client->dev, "%d-%04x", i2c_adapter_id(adap),
		     i2c_encode_flags_to_addr(client));
}