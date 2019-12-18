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
struct device {int dummy; } ;
struct pci_dev {scalar_t__ current_state; struct device dev; } ;
typedef  scalar_t__ pci_power_t ;

/* Variables and functions */
 scalar_t__ PCI_D3cold ; 
 scalar_t__ PCI_D3hot ; 
 int /*<<< orphan*/  device_may_wakeup (struct device*) ; 
 scalar_t__ pci_target_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_pci_need_resume (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 

bool pci_dev_need_resume(struct pci_dev *pci_dev)
{
	struct device *dev = &pci_dev->dev;
	pci_power_t target_state;

	if (!pm_runtime_suspended(dev) || platform_pci_need_resume(pci_dev))
		return true;

	target_state = pci_target_state(pci_dev, device_may_wakeup(dev));

	/*
	 * If the earlier platform check has not triggered, D3cold is just power
	 * removal on top of D3hot, so no need to resume the device in that
	 * case.
	 */
	return target_state != pci_dev->current_state &&
		target_state != PCI_D3cold &&
		pci_dev->current_state != PCI_D3hot;
}