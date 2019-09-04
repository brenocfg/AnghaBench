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
struct atl2_adapter {TYPE_1__ hw; int /*<<< orphan*/  link_chg_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  phy_config_timer; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ATL2_DOWN ; 
 int /*<<< orphan*/  atl2_force_ps (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void atl2_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl2_adapter *adapter = netdev_priv(netdev);

	/* flush_scheduled work may reschedule our watchdog task, so
	 * explicitly disable watchdog tasks from being rescheduled  */
	set_bit(__ATL2_DOWN, &adapter->flags);

	del_timer_sync(&adapter->watchdog_timer);
	del_timer_sync(&adapter->phy_config_timer);
	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->link_chg_task);

	unregister_netdev(netdev);

	atl2_force_ps(&adapter->hw);

	iounmap(adapter->hw.hw_addr);
	pci_release_regions(pdev);

	free_netdev(netdev);

	pci_disable_device(pdev);
}