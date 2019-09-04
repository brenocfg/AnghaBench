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
struct i2c_acpi_lookup {scalar_t__ search_handle; scalar_t__ adapter_handle; scalar_t__ speed; scalar_t__ min_speed; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 scalar_t__ i2c_acpi_do_lookup (struct acpi_device*,struct i2c_acpi_lookup*) ; 

__attribute__((used)) static acpi_status i2c_acpi_lookup_speed(acpi_handle handle, u32 level,
					   void *data, void **return_value)
{
	struct i2c_acpi_lookup *lookup = data;
	struct acpi_device *adev;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;

	if (i2c_acpi_do_lookup(adev, lookup))
		return AE_OK;

	if (lookup->search_handle != lookup->adapter_handle)
		return AE_OK;

	if (lookup->speed <= lookup->min_speed)
		lookup->min_speed = lookup->speed;

	return AE_OK;
}