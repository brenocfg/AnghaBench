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
struct pcie_device {int dummy; } ;
struct controller {int /*<<< orphan*/  hotplug_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_slot (struct controller*) ; 
 struct controller* get_service_data (struct pcie_device*) ; 
 int /*<<< orphan*/  pci_hp_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_shutdown_notification (struct controller*) ; 
 int /*<<< orphan*/  pciehp_release_ctrl (struct controller*) ; 

__attribute__((used)) static void pciehp_remove(struct pcie_device *dev)
{
	struct controller *ctrl = get_service_data(dev);

	pci_hp_del(&ctrl->hotplug_slot);
	pcie_shutdown_notification(ctrl);
	cleanup_slot(ctrl);
	pciehp_release_ctrl(ctrl);
}