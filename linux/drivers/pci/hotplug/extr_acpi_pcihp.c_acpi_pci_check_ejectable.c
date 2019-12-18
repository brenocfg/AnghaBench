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
struct pci_bus {int dummy; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_parent (scalar_t__,scalar_t__*) ; 
 scalar_t__ acpi_pci_get_bridge_handle (struct pci_bus*) ; 
 int pcihp_is_ejectable (scalar_t__) ; 

int acpi_pci_check_ejectable(struct pci_bus *pbus, acpi_handle handle)
{
	acpi_handle bridge_handle, parent_handle;

	bridge_handle = acpi_pci_get_bridge_handle(pbus);
	if (!bridge_handle)
		return 0;
	if ((ACPI_FAILURE(acpi_get_parent(handle, &parent_handle))))
		return 0;
	if (bridge_handle != parent_handle)
		return 0;
	return pcihp_is_ejectable(handle);
}