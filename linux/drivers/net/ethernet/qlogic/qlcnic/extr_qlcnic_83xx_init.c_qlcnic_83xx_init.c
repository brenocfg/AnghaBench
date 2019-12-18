#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_hardware_context {int msix_supported; int run_post; int /*<<< orphan*/ * mailbox; int /*<<< orphan*/  post_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct qlcnic_adapter {int rx_mac_learn; TYPE_3__ fw_work; TYPE_2__* nic_ops; int /*<<< orphan*/  dcb; int /*<<< orphan*/  idc_aen_work; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_5__ {int (* init_driver ) (struct qlcnic_adapter*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOTRECOVERABLE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_POST_FAST_MODE ; 
 int /*<<< orphan*/  QLC_83XX_POST_MEDIUM_MODE ; 
 int /*<<< orphan*/  QLC_83XX_POST_SLOW_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_83xx_check_hw_status (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_clear_function_resources (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_detach_mailbox_work (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mailbox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mbx_intr (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_get_fw_info (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_aen_work ; 
 int qlcnic_83xx_idc_init (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_poll_dev_state (int /*<<< orphan*/ *) ; 
 int qlcnic_83xx_init_mailbox_work (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_init_rings (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_initialize_nic (struct qlcnic_adapter*,int) ; 
 scalar_t__ qlcnic_83xx_read_flash_descriptor_table (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_read_flash_mfg_id (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_setup_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_dcb_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dcb_get_info (int /*<<< orphan*/ ) ; 
 int qlcnic_load_fw_file ; 
 int qlcnic_setup_intr (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_vf_init (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_teardown_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_use_msi_x ; 
 int stub1 (struct qlcnic_adapter*) ; 

int qlcnic_83xx_init(struct qlcnic_adapter *adapter, int pci_using_dac)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err = 0;

	adapter->rx_mac_learn = false;
	ahw->msix_supported = !!qlcnic_use_msi_x;

	/* Check if POST needs to be run */
	switch (qlcnic_load_fw_file) {
	case 2:
		ahw->post_mode = QLC_83XX_POST_FAST_MODE;
		ahw->run_post = true;
		break;
	case 3:
		ahw->post_mode = QLC_83XX_POST_MEDIUM_MODE;
		ahw->run_post = true;
		break;
	case 4:
		ahw->post_mode = QLC_83XX_POST_SLOW_MODE;
		ahw->run_post = true;
		break;
	default:
		ahw->run_post = false;
		break;
	}

	qlcnic_83xx_init_rings(adapter);

	err = qlcnic_83xx_init_mailbox_work(adapter);
	if (err)
		goto exit;

	if (qlcnic_sriov_vf_check(adapter)) {
		err = qlcnic_sriov_vf_init(adapter, pci_using_dac);
		if (err)
			goto detach_mbx;
		else
			return err;
	}

	if (qlcnic_83xx_read_flash_descriptor_table(adapter) ||
	    qlcnic_83xx_read_flash_mfg_id(adapter)) {
		dev_err(&adapter->pdev->dev, "Failed reading flash mfg id\n");
		err = -ENOTRECOVERABLE;
		goto detach_mbx;
	}

	err = qlcnic_83xx_check_hw_status(adapter);
	if (err)
		goto detach_mbx;

	err = qlcnic_83xx_get_fw_info(adapter);
	if (err)
		goto detach_mbx;

	err = qlcnic_83xx_idc_init(adapter);
	if (err)
		goto detach_mbx;

	err = qlcnic_setup_intr(adapter);
	if (err) {
		dev_err(&adapter->pdev->dev, "Failed to setup interrupt\n");
		goto disable_intr;
	}

	INIT_DELAYED_WORK(&adapter->idc_aen_work, qlcnic_83xx_idc_aen_work);

	err = qlcnic_83xx_setup_mbx_intr(adapter);
	if (err)
		goto disable_mbx_intr;

	qlcnic_83xx_clear_function_resources(adapter);
	qlcnic_dcb_enable(adapter->dcb);
	qlcnic_83xx_initialize_nic(adapter, 1);
	qlcnic_dcb_get_info(adapter->dcb);

	/* Configure default, SR-IOV or Virtual NIC mode of operation */
	err = qlcnic_83xx_configure_opmode(adapter);
	if (err)
		goto disable_mbx_intr;


	/* Perform operating mode specific initialization */
	err = adapter->nic_ops->init_driver(adapter);
	if (err)
		goto disable_mbx_intr;

	/* Periodically monitor device status */
	qlcnic_83xx_idc_poll_dev_state(&adapter->fw_work.work);
	return 0;

disable_mbx_intr:
	qlcnic_83xx_free_mbx_intr(adapter);

disable_intr:
	qlcnic_teardown_intr(adapter);

detach_mbx:
	qlcnic_83xx_detach_mailbox_work(adapter);
	qlcnic_83xx_free_mailbox(ahw->mailbox);
	ahw->mailbox = NULL;
exit:
	return err;
}