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
struct qlcnic_adapter {int /*<<< orphan*/  idc_aen_work; struct net_device* netdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_TERM ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  qlcnic_83xx_disable_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_cancel_idc_work (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_channel_cfg_cmd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_sriov_vf_shutdown(struct pci_dev *pdev)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;
	int retval;

	netif_device_detach(netdev);
	qlcnic_cancel_idc_work(adapter);

	if (netif_running(netdev))
		qlcnic_down(adapter, netdev);

	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);
	qlcnic_sriov_cfg_bc_intr(adapter, 0);
	qlcnic_83xx_disable_mbx_intr(adapter);
	cancel_delayed_work_sync(&adapter->idc_aen_work);

	retval = pci_save_state(pdev);
	if (retval)
		return retval;

	return 0;
}