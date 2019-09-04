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
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool acpi_fan_is_acpi4(struct acpi_device *device)
{
	return acpi_has_method(device->handle, "_FIF") &&
	       acpi_has_method(device->handle, "_FPS") &&
	       acpi_has_method(device->handle, "_FSL") &&
	       acpi_has_method(device->handle, "_FST");
}