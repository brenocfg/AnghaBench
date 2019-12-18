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
typedef  int u32 ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_pm_wakeup_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chromeos_tbmc_query_switch (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void chromeos_tbmc_notify(struct acpi_device *adev, u32 event)
{
	acpi_pm_wakeup_event(&adev->dev);
	switch (event) {
	case 0x80:
		chromeos_tbmc_query_switch(adev, adev->driver_data);
		break;
	default:
		dev_err(&adev->dev, "Unexpected event: 0x%08X\n", event);
	}
}