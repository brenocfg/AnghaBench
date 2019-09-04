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
struct pci_controller {int /*<<< orphan*/  bus; } ;
struct cxl_afu {struct pci_controller* phb; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_remove_root_bus (int /*<<< orphan*/ ) ; 

void cxl_pci_vphb_remove(struct cxl_afu *afu)
{
	struct pci_controller *phb;

	/* If there is no configuration record we won't have one of these */
	if (!afu || !afu->phb)
		return;

	phb = afu->phb;
	afu->phb = NULL;

	pci_remove_root_bus(phb->bus);
	/*
	 * We don't free phb here - that's handled by
	 * pcibios_free_controller_deferred()
	 */
}