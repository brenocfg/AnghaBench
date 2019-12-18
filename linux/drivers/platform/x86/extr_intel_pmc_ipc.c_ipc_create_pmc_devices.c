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
struct TYPE_2__ {int /*<<< orphan*/  tco_dev; int /*<<< orphan*/  punit_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  telem_res_inval; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_has_watchdog () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int ipc_create_punit_device () ; 
 int ipc_create_tco_device () ; 
 int ipc_create_telemetry_device () ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipc_create_pmc_devices(void)
{
	int ret;

	/* If we have ACPI based watchdog use that instead */
	if (!acpi_has_watchdog()) {
		ret = ipc_create_tco_device();
		if (ret) {
			dev_err(ipcdev.dev, "Failed to add tco platform device\n");
			return ret;
		}
	}

	ret = ipc_create_punit_device();
	if (ret) {
		dev_err(ipcdev.dev, "Failed to add punit platform device\n");
		platform_device_unregister(ipcdev.tco_dev);
		return ret;
	}

	if (!ipcdev.telem_res_inval) {
		ret = ipc_create_telemetry_device();
		if (ret) {
			dev_warn(ipcdev.dev,
				"Failed to add telemetry platform device\n");
			platform_device_unregister(ipcdev.punit_dev);
			platform_device_unregister(ipcdev.tco_dev);
		}
	}

	return ret;
}