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
struct nvkm_device {int dummy; } ;

/* Variables and functions */

void
nvkm_acpi_init(struct nvkm_device *device)
{
#ifdef CONFIG_ACPI
	device->acpi.nb.notifier_call = nvkm_acpi_ntfy;
	register_acpi_notifier(&device->acpi.nb);
#endif
}