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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_addr; } ;
struct atl1e_adapter {TYPE_1__ hw; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  atl1e_cancel_work (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_del_timer (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_force_ps (TYPE_1__*) ; 
 int /*<<< orphan*/  atl1e_free_ring_resources (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void atl1e_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl1e_adapter *adapter = netdev_priv(netdev);

	/*
	 * flush_scheduled work may reschedule our watchdog task, so
	 * explicitly disable watchdog tasks from being rescheduled
	 */
	set_bit(__AT_DOWN, &adapter->flags);

	atl1e_del_timer(adapter);
	atl1e_cancel_work(adapter);

	unregister_netdev(netdev);
	atl1e_free_ring_resources(adapter);
	atl1e_force_ps(&adapter->hw);
	pci_iounmap(pdev, adapter->hw.hw_addr);
	pci_release_regions(pdev);
	free_netdev(netdev);
	pci_disable_device(pdev);
}