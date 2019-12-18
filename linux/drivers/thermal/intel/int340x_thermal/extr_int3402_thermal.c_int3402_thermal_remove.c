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
struct platform_device {int dummy; } ;
struct int3402_thermal_data {int /*<<< orphan*/  int340x_zone; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int3402_notify ; 
 int /*<<< orphan*/  int340x_thermal_zone_remove (int /*<<< orphan*/ ) ; 
 struct int3402_thermal_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int int3402_thermal_remove(struct platform_device *pdev)
{
	struct int3402_thermal_data *d = platform_get_drvdata(pdev);

	acpi_remove_notify_handler(d->handle,
				   ACPI_DEVICE_NOTIFY, int3402_notify);
	int340x_thermal_zone_remove(d->int340x_zone);

	return 0;
}