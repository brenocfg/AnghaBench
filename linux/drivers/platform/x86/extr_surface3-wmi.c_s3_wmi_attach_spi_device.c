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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  SPI_TS_OBJ_NAME ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status s3_wmi_attach_spi_device(acpi_handle handle,
					    u32 level,
					    void *data,
					    void **return_value)
{
	struct acpi_device *adev, **ts_adev;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;

	ts_adev = data;

	if (strncmp(acpi_device_bid(adev), SPI_TS_OBJ_NAME,
	    strlen(SPI_TS_OBJ_NAME)))
		return AE_OK;

	if (*ts_adev) {
		pr_err("duplicate entry %s\n", SPI_TS_OBJ_NAME);
		return AE_OK;
	}

	*ts_adev = adev;

	return AE_OK;
}