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
struct pci_dev {TYPE_1__* link_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  aspm_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 

bool pcie_aspm_enabled(struct pci_dev *pdev)
{
	struct pci_dev *bridge = pci_upstream_bridge(pdev);
	bool ret;

	if (!bridge)
		return false;

	mutex_lock(&aspm_lock);
	ret = bridge->link_state ? !!bridge->link_state->aspm_enabled : false;
	mutex_unlock(&aspm_lock);

	return ret;
}