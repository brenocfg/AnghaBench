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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_INTERRUPT_HANDLED ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  acpi_device_notify_fixed ; 
 int /*<<< orphan*/  acpi_os_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static u32 acpi_device_fixed_event(void *data)
{
	acpi_os_execute(OSL_NOTIFY_HANDLER, acpi_device_notify_fixed, data);
	return ACPI_INTERRUPT_HANDLED;
}