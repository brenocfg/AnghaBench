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
struct dock_station {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  UNDOCK_EVENT ; 
 int /*<<< orphan*/  acpi_evaluate_ej0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_lck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  complete_undock (struct dock_station*) ; 
 int /*<<< orphan*/  dock_event (struct dock_station*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dock_in_progress (struct dock_station*) ; 
 scalar_t__ dock_present (struct dock_station*) ; 
 int /*<<< orphan*/  hot_remove_dock_devices (struct dock_station*) ; 
 int /*<<< orphan*/  undock (struct dock_station*) ; 

__attribute__((used)) static int handle_eject_request(struct dock_station *ds, u32 event)
{
	if (dock_in_progress(ds))
		return -EBUSY;

	/*
	 * here we need to generate the undock
	 * event prior to actually doing the undock
	 * so that the device struct still exists.
	 * Also, even send the dock event if the
	 * device is not present anymore
	 */
	dock_event(ds, event, UNDOCK_EVENT);

	hot_remove_dock_devices(ds);
	undock(ds);
	acpi_evaluate_lck(ds->handle, 0);
	acpi_evaluate_ej0(ds->handle);
	if (dock_present(ds)) {
		acpi_handle_err(ds->handle, "Unable to undock!\n");
		return -EBUSY;
	}
	complete_undock(ds);
	return 0;
}