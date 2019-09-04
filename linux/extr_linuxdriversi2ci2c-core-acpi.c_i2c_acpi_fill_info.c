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
struct i2c_board_info {int /*<<< orphan*/  flags; scalar_t__ addr; } ;
struct i2c_acpi_lookup {int index; int /*<<< orphan*/  speed; int /*<<< orphan*/  adapter_handle; int /*<<< orphan*/  device_handle; int /*<<< orphan*/  n; struct i2c_board_info* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  string_ptr; } ;
struct acpi_resource_i2c_serialbus {scalar_t__ type; scalar_t__ access_mode; int /*<<< orphan*/  connection_speed; scalar_t__ slave_address; TYPE_2__ resource_source; } ;
struct TYPE_3__ {struct acpi_resource_i2c_serialbus i2c_serial_bus; } ;
struct acpi_resource {scalar_t__ type; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_I2C_10BIT_MODE ; 
 scalar_t__ ACPI_RESOURCE_SERIAL_TYPE_I2C ; 
 scalar_t__ ACPI_RESOURCE_TYPE_SERIAL_BUS ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_CLIENT_TEN ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_acpi_fill_info(struct acpi_resource *ares, void *data)
{
	struct i2c_acpi_lookup *lookup = data;
	struct i2c_board_info *info = lookup->info;
	struct acpi_resource_i2c_serialbus *sb;
	acpi_status status;

	if (info->addr || ares->type != ACPI_RESOURCE_TYPE_SERIAL_BUS)
		return 1;

	sb = &ares->data.i2c_serial_bus;
	if (sb->type != ACPI_RESOURCE_SERIAL_TYPE_I2C)
		return 1;

	if (lookup->index != -1 && lookup->n++ != lookup->index)
		return 1;

	status = acpi_get_handle(lookup->device_handle,
				 sb->resource_source.string_ptr,
				 &lookup->adapter_handle);
	if (!ACPI_SUCCESS(status))
		return 1;

	info->addr = sb->slave_address;
	lookup->speed = sb->connection_speed;
	if (sb->access_mode == ACPI_I2C_10BIT_MODE)
		info->flags |= I2C_CLIENT_TEN;

	return 1;
}