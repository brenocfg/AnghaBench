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
struct ixgbevf_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  rss_key; int /*<<< orphan*/  hw; int /*<<< orphan*/  io_addr; int /*<<< orphan*/  service_task; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  __IXGBEVF_DISABLED ; 
 int /*<<< orphan*/  __IXGBEVF_REMOVING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hw_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_clear_interrupt_scheme (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset_interrupt_capability (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_stop_ipsec_offload (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ixgbevf_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct ixgbevf_adapter *adapter;
	bool disable_dev;

	if (!netdev)
		return;

	adapter = netdev_priv(netdev);

	set_bit(__IXGBEVF_REMOVING, &adapter->state);
	cancel_work_sync(&adapter->service_task);

	if (netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(netdev);

	ixgbevf_stop_ipsec_offload(adapter);
	ixgbevf_clear_interrupt_scheme(adapter);
	ixgbevf_reset_interrupt_capability(adapter);

	iounmap(adapter->io_addr);
	pci_release_regions(pdev);

	hw_dbg(&adapter->hw, "Remove complete\n");

	kfree(adapter->rss_key);
	disable_dev = !test_and_set_bit(__IXGBEVF_DISABLED, &adapter->state);
	free_netdev(netdev);

	if (disable_dev)
		pci_disable_device(pdev);
}