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
struct ni903x_wdt {int /*<<< orphan*/  wdd; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct ni903x_wdt* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  ni903x_wdd_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ni903x_acpi_remove(struct acpi_device *device)
{
	struct ni903x_wdt *wdt = acpi_driver_data(device);

	ni903x_wdd_stop(&wdt->wdd);
	watchdog_unregister_device(&wdt->wdd);

	return 0;
}