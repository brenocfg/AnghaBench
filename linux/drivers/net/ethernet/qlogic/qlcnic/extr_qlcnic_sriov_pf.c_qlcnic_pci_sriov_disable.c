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
struct qlcnic_adapter {int /*<<< orphan*/  portnum; struct net_device* netdev; int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_vfs_assigned (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_free_vlans (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_disable (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int qlcnic_pci_sriov_disable(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	if (pci_vfs_assigned(adapter->pdev)) {
		netdev_err(adapter->netdev,
			   "SR-IOV VFs belonging to port %d are assigned to VMs. SR-IOV can not be disabled on this port\n",
			   adapter->portnum);
		netdev_info(adapter->netdev,
			    "Please detach SR-IOV VFs belonging to port %d from VMs, and then try to disable SR-IOV on this port\n",
			    adapter->portnum);
		return -EPERM;
	}

	qlcnic_sriov_pf_disable(adapter);

	rtnl_lock();
	if (netif_running(netdev))
		__qlcnic_down(adapter, netdev);

	qlcnic_sriov_free_vlans(adapter);

	qlcnic_sriov_pf_cleanup(adapter);

	/* After disabling SRIOV re-init the driver in default mode
	   configure opmode based on op_mode of function
	 */
	if (qlcnic_83xx_configure_opmode(adapter)) {
		rtnl_unlock();
		return -EIO;
	}

	if (netif_running(netdev))
		__qlcnic_up(adapter, netdev);

	rtnl_unlock();
	return 0;
}