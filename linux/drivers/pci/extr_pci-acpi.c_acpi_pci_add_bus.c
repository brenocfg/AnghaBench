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
struct TYPE_2__ {int value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
struct pci_host_bridge {int ignore_reset_delay; } ;
struct pci_bus {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  RESET_DELAY_DSM ; 
 union acpi_object* acpi_evaluate_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_pci_disabled ; 
 int /*<<< orphan*/  acpi_pci_slot_enumerate (struct pci_bus*) ; 
 int /*<<< orphan*/  acpiphp_enumerate_slots (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_acpi_dsm_guid ; 
 struct pci_host_bridge* pci_find_host_bridge (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_is_root_bus (struct pci_bus*) ; 

void acpi_pci_add_bus(struct pci_bus *bus)
{
	union acpi_object *obj;
	struct pci_host_bridge *bridge;

	if (acpi_pci_disabled || !bus->bridge || !ACPI_HANDLE(bus->bridge))
		return;

	acpi_pci_slot_enumerate(bus);
	acpiphp_enumerate_slots(bus);

	/*
	 * For a host bridge, check its _DSM for function 8 and if
	 * that is available, mark it in pci_host_bridge.
	 */
	if (!pci_is_root_bus(bus))
		return;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(bus->bridge), &pci_acpi_dsm_guid, 3,
				RESET_DELAY_DSM, NULL);
	if (!obj)
		return;

	if (obj->type == ACPI_TYPE_INTEGER && obj->integer.value == 1) {
		bridge = pci_find_host_bridge(bus);
		bridge->ignore_reset_delay = 1;
	}
	ACPI_FREE(obj);
}