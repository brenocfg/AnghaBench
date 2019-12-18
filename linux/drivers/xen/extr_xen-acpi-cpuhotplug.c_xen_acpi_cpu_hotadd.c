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
struct acpi_processor {int /*<<< orphan*/  id; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ invalid_logical_cpuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_processor_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_hotadd_cpu (struct acpi_processor*) ; 
 int /*<<< orphan*/  xen_pcpu_hotplug_sync () ; 

__attribute__((used)) static acpi_status xen_acpi_cpu_hotadd(struct acpi_processor *pr)
{
	if (!is_processor_present(pr->handle))
		return AE_ERROR;

	pr->id = xen_hotadd_cpu(pr);
	if (invalid_logical_cpuid(pr->id))
		return AE_ERROR;

	/*
	 * Sync with Xen hypervisor, providing new /sys/.../xen_cpuX
	 * interface after cpu hotadded.
	 */
	xen_pcpu_hotplug_sync();

	return AE_OK;
}