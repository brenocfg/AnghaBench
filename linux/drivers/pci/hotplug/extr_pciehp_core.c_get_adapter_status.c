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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct hotplug_slot {int dummy; } ;
struct controller {TYPE_1__* pcie; } ;
struct TYPE_2__ {struct pci_dev* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_config_pm_runtime_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pciehp_card_present_or_link_active (struct controller*) ; 
 struct controller* to_ctrl (struct hotplug_slot*) ; 

__attribute__((used)) static int get_adapter_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	struct controller *ctrl = to_ctrl(hotplug_slot);
	struct pci_dev *pdev = ctrl->pcie->port;

	pci_config_pm_runtime_get(pdev);
	*value = pciehp_card_present_or_link_active(ctrl);
	pci_config_pm_runtime_put(pdev);
	return 0;
}