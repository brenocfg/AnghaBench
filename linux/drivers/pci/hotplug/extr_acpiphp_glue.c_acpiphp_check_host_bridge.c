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
struct acpiphp_bridge {int dummy; } ;
struct acpi_device {scalar_t__ hp; } ;
struct TYPE_2__ {struct acpiphp_bridge* root_bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_lock_hp_context () ; 
 int /*<<< orphan*/  acpi_unlock_hp_context () ; 
 int /*<<< orphan*/  acpiphp_check_bridge (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  get_bridge (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  put_bridge (struct acpiphp_bridge*) ; 
 TYPE_1__* to_acpiphp_root_context (scalar_t__) ; 

void acpiphp_check_host_bridge(struct acpi_device *adev)
{
	struct acpiphp_bridge *bridge = NULL;

	acpi_lock_hp_context();
	if (adev->hp) {
		bridge = to_acpiphp_root_context(adev->hp)->root_bridge;
		if (bridge)
			get_bridge(bridge);
	}
	acpi_unlock_hp_context();
	if (bridge) {
		pci_lock_rescan_remove();

		acpiphp_check_bridge(bridge);

		pci_unlock_rescan_remove();
		put_bridge(bridge);
	}
}