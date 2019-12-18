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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int crb_win; int ocm_win; } ;
struct netxen_adapter {TYPE_1__ ahw; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_POLL_DELAY ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netxen_fw_poll_work ; 
 int netxen_nic_attach (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_nic_detach (struct netxen_adapter*) ; 
 int netxen_nic_up (struct netxen_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  netxen_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_schedule_work (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int netxen_start_firmware (struct netxen_adapter*) ; 
 int /*<<< orphan*/  nx_decr_dev_ref_cnt (struct netxen_adapter*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct netxen_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netxen_nic_attach_func(struct pci_dev *pdev)
{
	struct netxen_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;
	int err;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	pci_set_power_state(pdev, PCI_D0);
	pci_set_master(pdev);
	pci_restore_state(pdev);

	adapter->ahw.crb_win = -1;
	adapter->ahw.ocm_win = -1;

	err = netxen_start_firmware(adapter);
	if (err) {
		dev_err(&pdev->dev, "failed to start firmware\n");
		return err;
	}

	if (netif_running(netdev)) {
		err = netxen_nic_attach(adapter);
		if (err)
			goto err_out;

		err = netxen_nic_up(adapter, netdev);
		if (err)
			goto err_out_detach;

		netxen_restore_indev_addr(netdev, NETDEV_UP);
	}

	netif_device_attach(netdev);
	netxen_schedule_work(adapter, netxen_fw_poll_work, FW_POLL_DELAY);
	return 0;

err_out_detach:
	netxen_nic_detach(adapter);
err_out:
	nx_decr_dev_ref_cnt(adapter);
	return err;
}