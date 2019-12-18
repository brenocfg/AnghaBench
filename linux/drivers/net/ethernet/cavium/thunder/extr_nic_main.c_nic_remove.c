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
struct nicpf {int flags; } ;

/* Variables and functions */
 int NIC_SRIOV_ENABLED ; 
 int /*<<< orphan*/  nic_unregister_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct nicpf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nic_remove(struct pci_dev *pdev)
{
	struct nicpf *nic = pci_get_drvdata(pdev);

	if (!nic)
		return;

	if (nic->flags & NIC_SRIOV_ENABLED)
		pci_disable_sriov(pdev);

	nic_unregister_interrupts(nic);
	pci_release_regions(pdev);

	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}