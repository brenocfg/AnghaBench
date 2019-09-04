#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  throttling; } ;
struct acpi_processor {int /*<<< orphan*/  id; TYPE_1__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  __acpi_processor_get_throttling ; 
 int call_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_processor*,int) ; 
 int /*<<< orphan*/  cpu_online (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_processor_get_throttling(struct acpi_processor *pr)
{
	if (!pr)
		return -EINVAL;

	if (!pr->flags.throttling)
		return -ENODEV;

	/*
	 * This is either called from the CPU hotplug callback of
	 * processor_driver or via the ACPI probe function. In the latter
	 * case the CPU is not guaranteed to be online. Both call sites are
	 * protected against CPU hotplug.
	 */
	if (!cpu_online(pr->id))
		return -ENODEV;

	return call_on_cpu(pr->id, __acpi_processor_get_throttling, pr, false);
}