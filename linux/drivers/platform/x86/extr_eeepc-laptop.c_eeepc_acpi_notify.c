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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct eeepc_laptop {int /*<<< orphan*/  backlight_device; int /*<<< orphan*/ * event_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_class; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 int ACPI_MAX_SYS_NOTIFY ; 
 int NOTIFY_BRN_MAX ; 
 int NOTIFY_BRN_MIN ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct eeepc_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int eeepc_backlight_notify (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  eeepc_input_notify (struct eeepc_laptop*,int) ; 

__attribute__((used)) static void eeepc_acpi_notify(struct acpi_device *device, u32 event)
{
	struct eeepc_laptop *eeepc = acpi_driver_data(device);
	int old_brightness, new_brightness;
	u16 count;

	if (event > ACPI_MAX_SYS_NOTIFY)
		return;
	count = eeepc->event_count[event % 128]++;
	acpi_bus_generate_netlink_event(device->pnp.device_class,
					dev_name(&device->dev), event,
					count);

	/* Brightness events are special */
	if (event < NOTIFY_BRN_MIN || event > NOTIFY_BRN_MAX) {
		eeepc_input_notify(eeepc, event);
		return;
	}

	/* Ignore them completely if the acpi video driver is used */
	if (!eeepc->backlight_device)
		return;

	/* Update the backlight device. */
	old_brightness = eeepc_backlight_notify(eeepc);

	/* Convert event to keypress (obsolescent hack) */
	new_brightness = event - NOTIFY_BRN_MIN;

	if (new_brightness < old_brightness) {
		event = NOTIFY_BRN_MIN; /* brightness down */
	} else if (new_brightness > old_brightness) {
		event = NOTIFY_BRN_MAX; /* brightness up */
	} else {
		/*
		 * no change in brightness - already at min/max,
		 * event will be desired value (or else ignored)
		 */
	}
	eeepc_input_notify(eeepc, event);
}