#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {int fc_autoneg; } ;
struct be_adapter {int /*<<< orphan*/  flags; TYPE_2__ phy; scalar_t__ num_vfs; int /*<<< orphan*/  if_handle; int /*<<< orphan*/  rx_fc; int /*<<< orphan*/  tx_fc; TYPE_1__* pdev; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  cmd_privileges; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  BE_FLAGS_SETUP_DONE ; 
 int /*<<< orphan*/  BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  IFLA_VF_LINK_STATE_AUTO ; 
 int /*<<< orphan*/  PORT_FWD_TYPE_PASSTHRU ; 
 int /*<<< orphan*/  be_alloc_sriov_res (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_get_flow_control (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_cmd_get_fn_privileges (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int be_cmd_get_func_config (struct be_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_cmd_get_fw_ver (struct be_adapter*) ; 
 int be_cmd_get_phy_info (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_req_native_mode (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_set_features (struct be_adapter*) ; 
 int be_cmd_set_flow_control (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_set_hsw_config (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_set_logical_link_config (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_func_init (struct be_adapter*) ; 
 int be_get_config (struct be_adapter*) ; 
 int be_get_resources (struct be_adapter*) ; 
 int be_if_create (struct be_adapter*) ; 
 int be_mac_setup (struct be_adapter*) ; 
 int be_msix_enable (struct be_adapter*) ; 
 scalar_t__ be_pause_supported (struct be_adapter*) ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 
 int /*<<< orphan*/  be_schedule_worker (struct be_adapter*) ; 
 int /*<<< orphan*/  be_setup_init (struct be_adapter*) ; 
 int be_setup_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  be_vf_setup (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int fw_major_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int be_setup(struct be_adapter *adapter)
{
	struct device *dev = &adapter->pdev->dev;
	int status;

	status = be_func_init(adapter);
	if (status)
		return status;

	be_setup_init(adapter);

	if (!lancer_chip(adapter))
		be_cmd_req_native_mode(adapter);

	/* invoke this cmd first to get pf_num and vf_num which are needed
	 * for issuing profile related cmds
	 */
	if (!BEx_chip(adapter)) {
		status = be_cmd_get_func_config(adapter, NULL);
		if (status)
			return status;
	}

	status = be_get_config(adapter);
	if (status)
		goto err;

	if (!BE2_chip(adapter) && be_physfn(adapter))
		be_alloc_sriov_res(adapter);

	status = be_get_resources(adapter);
	if (status)
		goto err;

	status = be_msix_enable(adapter);
	if (status)
		goto err;

	/* will enable all the needed filter flags in be_open() */
	status = be_if_create(adapter);
	if (status)
		goto err;

	/* Updating real_num_tx/rx_queues() requires rtnl_lock() */
	rtnl_lock();
	status = be_setup_queues(adapter);
	rtnl_unlock();
	if (status)
		goto err;

	be_cmd_get_fn_privileges(adapter, &adapter->cmd_privileges, 0);

	status = be_mac_setup(adapter);
	if (status)
		goto err;

	be_cmd_get_fw_ver(adapter);
	dev_info(dev, "FW version is %s\n", adapter->fw_ver);

	if (BE2_chip(adapter) && fw_major_num(adapter->fw_ver) < 4) {
		dev_err(dev, "Firmware on card is old(%s), IRQs may not work",
			adapter->fw_ver);
		dev_err(dev, "Please upgrade firmware to version >= 4.0\n");
	}

	status = be_cmd_set_flow_control(adapter, adapter->tx_fc,
					 adapter->rx_fc);
	if (status)
		be_cmd_get_flow_control(adapter, &adapter->tx_fc,
					&adapter->rx_fc);

	dev_info(&adapter->pdev->dev, "HW Flow control - TX:%d RX:%d\n",
		 adapter->tx_fc, adapter->rx_fc);

	if (be_physfn(adapter))
		be_cmd_set_logical_link_config(adapter,
					       IFLA_VF_LINK_STATE_AUTO, 0);

	/* BE3 EVB echoes broadcast/multicast packets back to PF's vport
	 * confusing a linux bridge or OVS that it might be connected to.
	 * Set the EVB to PASSTHRU mode which effectively disables the EVB
	 * when SRIOV is not enabled.
	 */
	if (BE3_chip(adapter))
		be_cmd_set_hsw_config(adapter, 0, 0, adapter->if_handle,
				      PORT_FWD_TYPE_PASSTHRU, 0);

	if (adapter->num_vfs)
		be_vf_setup(adapter);

	status = be_cmd_get_phy_info(adapter);
	if (!status && be_pause_supported(adapter))
		adapter->phy.fc_autoneg = 1;

	if (be_physfn(adapter) && !lancer_chip(adapter))
		be_cmd_set_features(adapter);

	be_schedule_worker(adapter);
	adapter->flags |= BE_FLAGS_SETUP_DONE;
	return 0;
err:
	be_clear(adapter);
	return status;
}