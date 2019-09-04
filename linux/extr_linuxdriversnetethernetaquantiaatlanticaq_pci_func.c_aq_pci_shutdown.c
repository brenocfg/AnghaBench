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
struct pci_dev {int dummy; } ;
struct aq_nic_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  aq_nic_shutdown (struct aq_nic_s*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct aq_nic_s* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int) ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void aq_pci_shutdown(struct pci_dev *pdev)
{
	struct aq_nic_s *self = pci_get_drvdata(pdev);

	aq_nic_shutdown(self);

	pci_disable_device(pdev);

	if (system_state == SYSTEM_POWER_OFF) {
		pci_wake_from_d3(pdev, false);
		pci_set_power_state(pdev, PCI_D3hot);
	}
}