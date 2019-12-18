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
struct acpiphp_root_context {int dummy; } ;
struct acpiphp_bridge {TYPE_1__* pci_bus; } ;
struct acpi_device {int /*<<< orphan*/ * hp; } ;
struct TYPE_2__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_lock_hp_context () ; 
 int /*<<< orphan*/  acpi_unlock_hp_context () ; 
 int /*<<< orphan*/  cleanup_bridge (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  kfree (struct acpiphp_root_context*) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  put_bridge (struct acpiphp_bridge*) ; 
 struct acpiphp_root_context* to_acpiphp_root_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpiphp_drop_bridge(struct acpiphp_bridge *bridge)
{
	if (pci_is_root_bus(bridge->pci_bus)) {
		struct acpiphp_root_context *root_context;
		struct acpi_device *adev;

		acpi_lock_hp_context();
		adev = ACPI_COMPANION(bridge->pci_bus->bridge);
		root_context = to_acpiphp_root_context(adev->hp);
		adev->hp = NULL;
		acpi_unlock_hp_context();
		kfree(root_context);
	}
	cleanup_bridge(bridge);
	put_bridge(bridge);
}