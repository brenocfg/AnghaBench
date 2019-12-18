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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int toshiba_bluetooth_enable(acpi_handle handle)
{
	acpi_status result;

	result = acpi_evaluate_object(handle, "AUSB", NULL, NULL);
	if (ACPI_FAILURE(result)) {
		pr_err("Could not attach USB Bluetooth device\n");
		return -ENXIO;
	}

	result = acpi_evaluate_object(handle, "BTPO", NULL, NULL);
	if (ACPI_FAILURE(result)) {
		pr_err("Could not power ON Bluetooth device\n");
		return -ENXIO;
	}

	return 0;
}