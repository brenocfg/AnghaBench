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
struct qlcnic_adapter {int need_fw_reset; int /*<<< orphan*/  state; int /*<<< orphan*/ * msix_entries; TYPE_1__* ahw; struct net_device* netdev; } ;
struct pci_dev {int /*<<< orphan*/  error_state; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ op_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  QLCDB (struct qlcnic_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QLCNIC_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLCNIC_DEV_INITIALIZING ; 
 scalar_t__ QLCNIC_NON_PRIV_FUNC ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_AER ; 
 int /*<<< orphan*/  __QLCNIC_START_FW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 
 int qlcnic_attach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_clr_all_drv_state (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_clr_drv_state (struct qlcnic_adapter*) ; 
 int qlcnic_is_first_func (struct pci_dev*) ; 
 int /*<<< orphan*/  qlcnic_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 int qlcnic_setup_intr (struct qlcnic_adapter*) ; 
 int qlcnic_start_firmware (struct qlcnic_adapter*) ; 
 int qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_attach_func(struct pci_dev *pdev)
{
	int err, first_func;
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;

	pdev->error_state = pci_channel_io_normal;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	pci_set_master(pdev);
	pci_restore_state(pdev);

	first_func = qlcnic_is_first_func(pdev);

	if (qlcnic_api_lock(adapter))
		return -EINVAL;

	if (adapter->ahw->op_mode != QLCNIC_NON_PRIV_FUNC && first_func) {
		adapter->need_fw_reset = 1;
		set_bit(__QLCNIC_START_FW, &adapter->state);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_INITIALIZING);
		QLCDB(adapter, DRV, "Restarting fw\n");
	}
	qlcnic_api_unlock(adapter);

	err = qlcnic_start_firmware(adapter);
	if (err)
		return err;

	qlcnic_clr_drv_state(adapter);
	kfree(adapter->msix_entries);
	adapter->msix_entries = NULL;
	err = qlcnic_setup_intr(adapter);

	if (err) {
		kfree(adapter->msix_entries);
		netdev_err(netdev, "failed to setup interrupt\n");
		return err;
	}

	if (netif_running(netdev)) {
		err = qlcnic_attach(adapter);
		if (err) {
			qlcnic_clr_all_drv_state(adapter, 1);
			clear_bit(__QLCNIC_AER, &adapter->state);
			netif_device_attach(netdev);
			return err;
		}

		err = qlcnic_up(adapter, netdev);
		if (err)
			goto done;

		qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	}
 done:
	netif_device_attach(netdev);
	return err;
}