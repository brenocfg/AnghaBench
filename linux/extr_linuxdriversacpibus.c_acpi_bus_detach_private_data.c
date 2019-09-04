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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_bus_private_data_handler ; 
 int /*<<< orphan*/  acpi_detach_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void acpi_bus_detach_private_data(acpi_handle handle)
{
	acpi_detach_data(handle, acpi_bus_private_data_handler);
}