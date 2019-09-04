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
struct net_device {int dummy; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  __IXGBEVF_DISABLED ; 
 int /*<<< orphan*/  __IXGBEVF_SERVICE_INITED ; 
 int /*<<< orphan*/  ixgbevf_close_suspend (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t ixgbevf_io_error_detected(struct pci_dev *pdev,
						  pci_channel_state_t state)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);

	if (!test_bit(__IXGBEVF_SERVICE_INITED, &adapter->state))
		return PCI_ERS_RESULT_DISCONNECT;

	rtnl_lock();
	netif_device_detach(netdev);

	if (netif_running(netdev))
		ixgbevf_close_suspend(adapter);

	if (state == pci_channel_io_perm_failure) {
		rtnl_unlock();
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (!test_and_set_bit(__IXGBEVF_DISABLED, &adapter->state))
		pci_disable_device(pdev);
	rtnl_unlock();

	/* Request a slot slot reset. */
	return PCI_ERS_RESULT_NEED_RESET;
}