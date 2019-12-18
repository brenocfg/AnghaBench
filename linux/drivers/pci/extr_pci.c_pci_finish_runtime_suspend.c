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
struct pci_dev {int runtime_d3cold; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ pci_power_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PCI_D3cold ; 
 scalar_t__ PCI_POWER_ERROR ; 
 int /*<<< orphan*/  __pci_enable_wake (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_run_wake (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,scalar_t__,int) ; 
 int pci_set_power_state (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_target_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

int pci_finish_runtime_suspend(struct pci_dev *dev)
{
	pci_power_t target_state;
	int error;

	target_state = pci_target_state(dev, device_can_wakeup(&dev->dev));
	if (target_state == PCI_POWER_ERROR)
		return -EIO;

	dev->runtime_d3cold = target_state == PCI_D3cold;

	__pci_enable_wake(dev, target_state, pci_dev_run_wake(dev));

	error = pci_set_power_state(dev, target_state);

	if (error) {
		pci_enable_wake(dev, target_state, false);
		dev->runtime_d3cold = false;
	}

	return error;
}