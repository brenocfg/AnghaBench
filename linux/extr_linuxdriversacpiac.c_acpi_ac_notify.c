#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  device_class; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_3__ pnp; } ;
struct acpi_ac {TYPE_2__* charger; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
#define  ACPI_AC_NOTIFY_STATUS 130 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_NOTIFY_BUS_CHECK 129 
#define  ACPI_NOTIFY_DEVICE_CHECK 128 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  ac_sleep_before_get_state_ms ; 
 int /*<<< orphan*/  acpi_ac_get_state (struct acpi_ac*) ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct acpi_ac* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_notifier_call_chain (struct acpi_device*,int,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_ac_notify(struct acpi_device *device, u32 event)
{
	struct acpi_ac *ac = acpi_driver_data(device);

	if (!ac)
		return;

	switch (event) {
	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Unsupported event [0x%x]\n", event));
	/* fall through */
	case ACPI_AC_NOTIFY_STATUS:
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:
		/*
		 * A buggy BIOS may notify AC first and then sleep for
		 * a specific time before doing actual operations in the
		 * EC event handler (_Qxx). This will cause the AC state
		 * reported by the ACPI event to be incorrect, so wait for a
		 * specific time for the EC event handler to make progress.
		 */
		if (ac_sleep_before_get_state_ms > 0)
			msleep(ac_sleep_before_get_state_ms);

		acpi_ac_get_state(ac);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event,
						  (u32) ac->state);
		acpi_notifier_call_chain(device, event, (u32) ac->state);
		kobject_uevent(&ac->charger->dev.kobj, KOBJ_CHANGE);
	}

	return;
}