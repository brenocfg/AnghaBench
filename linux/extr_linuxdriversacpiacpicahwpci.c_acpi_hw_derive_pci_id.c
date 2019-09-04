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
struct acpi_pci_id {int dummy; } ;
struct acpi_pci_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  acpi_hw_build_pci_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_pci_device**) ; 
 int /*<<< orphan*/  acpi_hw_delete_pci_list (struct acpi_pci_device*) ; 
 int /*<<< orphan*/  acpi_hw_process_pci_list (struct acpi_pci_id*,struct acpi_pci_device*) ; 
 int /*<<< orphan*/  hw_derive_pci_id ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_hw_derive_pci_id(struct acpi_pci_id *pci_id,
		      acpi_handle root_pci_device, acpi_handle pci_region)
{
	acpi_status status;
	struct acpi_pci_device *list_head;

	ACPI_FUNCTION_TRACE(hw_derive_pci_id);

	if (!pci_id) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Build a list of PCI devices, from pci_region up to root_pci_device */

	status =
	    acpi_hw_build_pci_list(root_pci_device, pci_region, &list_head);
	if (ACPI_SUCCESS(status)) {

		/* Walk the list, updating the PCI device/function/bus numbers */

		status = acpi_hw_process_pci_list(pci_id, list_head);

		/* Delete the list */

		acpi_hw_delete_pci_list(list_head);
	}

	return_ACPI_STATUS(status);
}