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
struct TYPE_2__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  fwnode; } ;
struct hv_pcibus_device {scalar_t__ state; TYPE_1__ sysdata; int /*<<< orphan*/  wq; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  resources_for_children; int /*<<< orphan*/  cfg_addr; int /*<<< orphan*/  pci_bus; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  hv_free_config_window (struct hv_pcibus_device*) ; 
 struct hv_pcibus_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_pci_bus_exit (struct hv_device*) ; 
 int /*<<< orphan*/  hv_pci_free_bridge_windows (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  hv_pci_remove_slots (struct hv_pcibus_device*) ; 
 scalar_t__ hv_pcibus_installed ; 
 scalar_t__ hv_pcibus_removed ; 
 int /*<<< orphan*/  hv_put_dom_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_free_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_remove_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  put_hvpcibus (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hv_pci_remove(struct hv_device *hdev)
{
	struct hv_pcibus_device *hbus;

	hbus = hv_get_drvdata(hdev);
	if (hbus->state == hv_pcibus_installed) {
		/* Remove the bus from PCI's point of view. */
		pci_lock_rescan_remove();
		pci_stop_root_bus(hbus->pci_bus);
		hv_pci_remove_slots(hbus);
		pci_remove_root_bus(hbus->pci_bus);
		pci_unlock_rescan_remove();
		hbus->state = hv_pcibus_removed;
	}

	hv_pci_bus_exit(hdev);

	vmbus_close(hdev->channel);

	iounmap(hbus->cfg_addr);
	hv_free_config_window(hbus);
	pci_free_resource_list(&hbus->resources_for_children);
	hv_pci_free_bridge_windows(hbus);
	irq_domain_remove(hbus->irq_domain);
	irq_domain_free_fwnode(hbus->sysdata.fwnode);
	put_hvpcibus(hbus);
	wait_for_completion(&hbus->remove_event);
	destroy_workqueue(hbus->wq);

	hv_put_dom_num(hbus->sysdata.domain);

	free_page((unsigned long)hbus);
	return 0;
}