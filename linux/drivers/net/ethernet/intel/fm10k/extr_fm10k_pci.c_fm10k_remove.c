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
struct net_device {scalar_t__ reg_state; } ;
struct fm10k_intfc {scalar_t__ uc_addr; scalar_t__ sw_addr; int /*<<< orphan*/  glort; int /*<<< orphan*/  service_timer; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm10k_clear_macvlan_queue (struct fm10k_intfc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_clear_queueing_scheme (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_dbg_intfc_exit (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_iov_disable (struct pci_dev*) ; 
 int /*<<< orphan*/  fm10k_mbx_free_irq (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_stop_macvlan_task (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_stop_service_event (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct fm10k_intfc* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void fm10k_remove(struct pci_dev *pdev)
{
	struct fm10k_intfc *interface = pci_get_drvdata(pdev);
	struct net_device *netdev = interface->netdev;

	del_timer_sync(&interface->service_timer);

	fm10k_stop_service_event(interface);
	fm10k_stop_macvlan_task(interface);

	/* Remove all pending MAC/VLAN requests */
	fm10k_clear_macvlan_queue(interface, interface->glort, true);

	/* free netdev, this may bounce the interrupts due to setup_tc */
	if (netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(netdev);

	/* release VFs */
	fm10k_iov_disable(pdev);

	/* disable mailbox interrupt */
	fm10k_mbx_free_irq(interface);

	/* free interrupts */
	fm10k_clear_queueing_scheme(interface);

	/* remove any debugfs interfaces */
	fm10k_dbg_intfc_exit(interface);

	if (interface->sw_addr)
		iounmap(interface->sw_addr);
	iounmap(interface->uc_addr);

	free_netdev(netdev);

	pci_release_mem_regions(pdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
}