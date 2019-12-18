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
struct pci_dev {int pme_poll; scalar_t__ current_state; int /*<<< orphan*/  subordinate; int /*<<< orphan*/  dev; scalar_t__ pme_support; } ;
struct acpi_device_wakeup_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_D3cold ; 
 int /*<<< orphan*/  pci_check_pme_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pme_wakeup_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wakeup_event (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_request_resume (int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_acpi_wake_dev(struct acpi_device_wakeup_context *context)
{
	struct pci_dev *pci_dev;

	pci_dev = to_pci_dev(context->dev);

	if (pci_dev->pme_poll)
		pci_dev->pme_poll = false;

	if (pci_dev->current_state == PCI_D3cold) {
		pci_wakeup_event(pci_dev);
		pm_request_resume(&pci_dev->dev);
		return;
	}

	/* Clear PME Status if set. */
	if (pci_dev->pme_support)
		pci_check_pme_status(pci_dev);

	pci_wakeup_event(pci_dev);
	pm_request_resume(&pci_dev->dev);

	pci_pme_wakeup_bus(pci_dev->subordinate);
}