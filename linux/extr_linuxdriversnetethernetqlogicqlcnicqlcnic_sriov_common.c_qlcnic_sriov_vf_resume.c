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
struct qlcnic_adapter {struct net_device* netdev; TYPE_1__* ahw; } ;
struct qlc_83xx_idc {int /*<<< orphan*/  delay; int /*<<< orphan*/  status; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct qlc_83xx_idc idc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int /*<<< orphan*/  QLC_83XX_MODULE_LOADED ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_mbx_interrupt (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_schedule_work (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_channel_cfg_cmd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_poll_dev_state ; 
 int qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_sriov_vf_resume(struct qlcnic_adapter *adapter)
{
	struct qlc_83xx_idc *idc = &adapter->ahw->idc;
	struct net_device *netdev = adapter->netdev;
	int err;

	set_bit(QLC_83XX_MODULE_LOADED, &idc->status);
	qlcnic_83xx_enable_mbx_interrupt(adapter);
	err = qlcnic_sriov_cfg_bc_intr(adapter, 1);
	if (err)
		return err;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	if (!err) {
		if (netif_running(netdev)) {
			err = qlcnic_up(adapter, netdev);
			if (!err)
				qlcnic_restore_indev_addr(netdev, NETDEV_UP);
		}
	}

	netif_device_attach(netdev);
	qlcnic_schedule_work(adapter, qlcnic_sriov_vf_poll_dev_state,
			     idc->delay);
	return err;
}