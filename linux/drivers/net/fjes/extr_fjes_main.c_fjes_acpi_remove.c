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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static int fjes_acpi_remove(struct acpi_device *device)
{
	struct platform_device *plat_dev;

	plat_dev = (struct platform_device *)acpi_driver_data(device);
	platform_device_unregister(plat_dev);

	return 0;
}