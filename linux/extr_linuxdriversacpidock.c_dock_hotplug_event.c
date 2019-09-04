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
typedef  int /*<<< orphan*/  u32 ;
struct dock_dependent_device {struct acpi_device* adev; } ;
struct acpi_device {TYPE_1__* hp; } ;
typedef  enum dock_callback_type { ____Placeholder_dock_callback_type } dock_callback_type ;
struct TYPE_2__ {void (* fixup ) (struct acpi_device*) ;void (* uevent ) (struct acpi_device*,int /*<<< orphan*/ ) ;int (* notify ) (struct acpi_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DOCK_CALL_FIXUP ; 
 int DOCK_CALL_UEVENT ; 
 int /*<<< orphan*/  acpi_lock_hp_context () ; 
 int /*<<< orphan*/  acpi_unlock_hp_context () ; 

__attribute__((used)) static void dock_hotplug_event(struct dock_dependent_device *dd, u32 event,
			       enum dock_callback_type cb_type)
{
	struct acpi_device *adev = dd->adev;

	acpi_lock_hp_context();

	if (!adev->hp)
		goto out;

	if (cb_type == DOCK_CALL_FIXUP) {
		void (*fixup)(struct acpi_device *);

		fixup = adev->hp->fixup;
		if (fixup) {
			acpi_unlock_hp_context();
			fixup(adev);
			return;
		}
	} else if (cb_type == DOCK_CALL_UEVENT) {
		void (*uevent)(struct acpi_device *, u32);

		uevent = adev->hp->uevent;
		if (uevent) {
			acpi_unlock_hp_context();
			uevent(adev, event);
			return;
		}
	} else {
		int (*notify)(struct acpi_device *, u32);

		notify = adev->hp->notify;
		if (notify) {
			acpi_unlock_hp_context();
			notify(adev, event);
			return;
		}
	}

 out:
	acpi_unlock_hp_context();
}