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
struct eeepc_laptop {int /*<<< orphan*/  cm_supported; int /*<<< orphan*/  handle; TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  present; } ;
struct TYPE_4__ {TYPE_1__ status; } ;

/* Variables and functions */
 unsigned int DISABLE_ASL_DISPLAYSWITCH ; 
 unsigned int DISABLE_ASL_WLAN ; 
 int ENODEV ; 
 int acpi_bus_get_status (TYPE_2__*) ; 
 int /*<<< orphan*/  cmsg_quirks (struct eeepc_laptop*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,unsigned int) ; 
 scalar_t__ read_acpi_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int eeepc_acpi_init(struct eeepc_laptop *eeepc)
{
	unsigned int init_flags;
	int result;

	result = acpi_bus_get_status(eeepc->device);
	if (result)
		return result;
	if (!eeepc->device->status.present) {
		pr_err("Hotkey device not present, aborting\n");
		return -ENODEV;
	}

	init_flags = DISABLE_ASL_WLAN | DISABLE_ASL_DISPLAYSWITCH;
	pr_notice("Hotkey init flags 0x%x\n", init_flags);

	if (write_acpi_int(eeepc->handle, "INIT", init_flags)) {
		pr_err("Hotkey initialization failed\n");
		return -ENODEV;
	}

	/* get control methods supported */
	if (read_acpi_int(eeepc->handle, "CMSG", &eeepc->cm_supported)) {
		pr_err("Get control methods supported failed\n");
		return -ENODEV;
	}
	cmsg_quirks(eeepc);
	pr_info("Get control methods supported: 0x%x\n", eeepc->cm_supported);

	return 0;
}