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
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_pad_notify ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_acpi_pad_idle_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_cpu_lock ; 

__attribute__((used)) static int acpi_pad_remove(struct acpi_device *device)
{
	mutex_lock(&xen_cpu_lock);
	xen_acpi_pad_idle_cpus(0);
	mutex_unlock(&xen_cpu_lock);

	acpi_remove_notify_handler(device->handle,
		ACPI_DEVICE_NOTIFY, acpi_pad_notify);
	return 0;
}