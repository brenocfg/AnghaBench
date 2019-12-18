#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_3__ {TYPE_2__ nb; } ;
struct nvkm_device {TYPE_1__ acpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_acpi_ntfy ; 
 int /*<<< orphan*/  register_acpi_notifier (TYPE_2__*) ; 

void
nvkm_acpi_init(struct nvkm_device *device)
{
#ifdef CONFIG_ACPI
	device->acpi.nb.notifier_call = nvkm_acpi_ntfy;
	register_acpi_notifier(&device->acpi.nb);
#endif
}