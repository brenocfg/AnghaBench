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
struct acpi_hotplug_context {int (* notify ) (struct acpi_device*,u32) ;void (* uevent ) (struct acpi_device*,u32) ;} ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_lock_hp_context () ; 
 int /*<<< orphan*/  acpi_set_hp_context (struct acpi_device*,struct acpi_hotplug_context*) ; 
 int /*<<< orphan*/  acpi_unlock_hp_context () ; 

void acpi_initialize_hp_context(struct acpi_device *adev,
				struct acpi_hotplug_context *hp,
				int (*notify)(struct acpi_device *, u32),
				void (*uevent)(struct acpi_device *, u32))
{
	acpi_lock_hp_context();
	hp->notify = notify;
	hp->uevent = uevent;
	acpi_set_hp_context(adev, hp);
	acpi_unlock_hp_context();
}