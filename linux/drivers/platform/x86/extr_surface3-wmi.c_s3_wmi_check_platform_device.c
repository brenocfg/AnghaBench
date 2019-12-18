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
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {struct acpi_device* touchscreen_adev; struct acpi_device* pnp0c0d_adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUTTON_HID_LID ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  SPI_CTL_OBJ_NAME ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_device**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 TYPE_1__ s3_wmi ; 
 int /*<<< orphan*/  s3_wmi_attach_spi_device ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3_wmi_check_platform_device(struct device *dev, void *data)
{
	struct acpi_device *adev, *ts_adev = NULL;
	acpi_handle handle;
	acpi_status status;

	/* ignore non ACPI devices */
	handle = ACPI_HANDLE(dev);
	if (!handle || acpi_bus_get_device(handle, &adev))
		return 0;

	/* check for LID ACPI switch */
	if (!strcmp(ACPI_BUTTON_HID_LID, acpi_device_hid(adev))) {
		s3_wmi.pnp0c0d_adev = adev;
		return 0;
	}

	/* ignore non SPI controllers */
	if (strncmp(acpi_device_bid(adev), SPI_CTL_OBJ_NAME,
	    strlen(SPI_CTL_OBJ_NAME)))
		return 0;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     s3_wmi_attach_spi_device, NULL,
				     &ts_adev, NULL);
	if (ACPI_FAILURE(status))
		dev_warn(dev, "failed to enumerate SPI slaves\n");

	if (!ts_adev)
		return 0;

	s3_wmi.touchscreen_adev = ts_adev;

	return 0;
}