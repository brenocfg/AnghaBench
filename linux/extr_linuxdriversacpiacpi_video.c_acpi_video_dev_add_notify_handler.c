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
struct TYPE_2__ {int notify; } ;
struct acpi_video_device {TYPE_1__ flags; struct acpi_device* dev; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_video_device*) ; 
 int /*<<< orphan*/  acpi_video_device_notify ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void acpi_video_dev_add_notify_handler(struct acpi_video_device *device)
{
	acpi_status status;
	struct acpi_device *adev = device->dev;

	status = acpi_install_notify_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					     acpi_video_device_notify, device);
	if (ACPI_FAILURE(status))
		dev_err(&adev->dev, "Error installing notify handler\n");
	else
		device->flags.notify = 1;
}