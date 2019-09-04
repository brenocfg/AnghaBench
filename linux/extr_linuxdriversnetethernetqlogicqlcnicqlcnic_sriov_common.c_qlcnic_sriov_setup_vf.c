#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_3__* netdev; TYPE_4__* pdev; int /*<<< orphan*/  vf_mc_list; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  delay; } ;
struct TYPE_6__ {int total_nic_func; TYPE_1__ idc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_TERM ; 
 int /*<<< orphan*/  QLCNIC_SINGLE_RING ; 
 int /*<<< orphan*/  QLCNIC_VLAN_FILTERING ; 
 int /*<<< orphan*/  __qlcnic_sriov_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_4__*,struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mbx_intr (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_setup_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_schedule_work (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_set_sds_ring_count (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_set_tx_ring_count (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int qlcnic_setup_intr (struct qlcnic_adapter*) ; 
 int qlcnic_setup_netdev (struct qlcnic_adapter*,TYPE_3__*,int) ; 
 int qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_channel_cfg_cmd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_get_vf_acl (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_init (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_vf_init_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_poll_dev_state ; 
 int /*<<< orphan*/  qlcnic_teardown_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_use_msi ; 
 int /*<<< orphan*/  qlcnic_use_msi_x ; 

__attribute__((used)) static int qlcnic_sriov_setup_vf(struct qlcnic_adapter *adapter,
				 int pci_using_dac)
{
	int err;

	adapter->flags |= QLCNIC_VLAN_FILTERING;
	adapter->ahw->total_nic_func = 1;
	INIT_LIST_HEAD(&adapter->vf_mc_list);
	if (!qlcnic_use_msi_x && !!qlcnic_use_msi)
		dev_warn(&adapter->pdev->dev,
			 "Device does not support MSI interrupts\n");

	/* compute and set default and max tx/sds rings */
	qlcnic_set_tx_ring_count(adapter, QLCNIC_SINGLE_RING);
	qlcnic_set_sds_ring_count(adapter, QLCNIC_SINGLE_RING);

	err = qlcnic_setup_intr(adapter);
	if (err) {
		dev_err(&adapter->pdev->dev, "Failed to setup interrupt\n");
		goto err_out_disable_msi;
	}

	err = qlcnic_83xx_setup_mbx_intr(adapter);
	if (err)
		goto err_out_disable_msi;

	err = qlcnic_sriov_init(adapter, 1);
	if (err)
		goto err_out_disable_mbx_intr;

	err = qlcnic_sriov_cfg_bc_intr(adapter, 1);
	if (err)
		goto err_out_cleanup_sriov;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	if (err)
		goto err_out_disable_bc_intr;

	err = qlcnic_sriov_vf_init_driver(adapter);
	if (err)
		goto err_out_send_channel_term;

	err = qlcnic_sriov_get_vf_acl(adapter);
	if (err)
		goto err_out_send_channel_term;

	err = qlcnic_setup_netdev(adapter, adapter->netdev, pci_using_dac);
	if (err)
		goto err_out_send_channel_term;

	pci_set_drvdata(adapter->pdev, adapter);
	dev_info(&adapter->pdev->dev, "%s: XGbE port initialized\n",
		 adapter->netdev->name);

	qlcnic_schedule_work(adapter, qlcnic_sriov_vf_poll_dev_state,
			     adapter->ahw->idc.delay);
	return 0;

err_out_send_channel_term:
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);

err_out_disable_bc_intr:
	qlcnic_sriov_cfg_bc_intr(adapter, 0);

err_out_cleanup_sriov:
	__qlcnic_sriov_cleanup(adapter);

err_out_disable_mbx_intr:
	qlcnic_83xx_free_mbx_intr(adapter);

err_out_disable_msi:
	qlcnic_teardown_intr(adapter);
	return err;
}