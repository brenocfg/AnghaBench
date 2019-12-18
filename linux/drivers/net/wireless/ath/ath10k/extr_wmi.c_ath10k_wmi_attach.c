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
struct TYPE_6__ {int /*<<< orphan*/  mgmt_pending_tx; int /*<<< orphan*/  radar_confirm; int /*<<< orphan*/  barrier; int /*<<< orphan*/  unified_ready; int /*<<< orphan*/  service_ready; int /*<<< orphan*/ * peer_flags; int /*<<< orphan*/ * pdev_param; int /*<<< orphan*/ * vdev_param; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * cmd; } ;
struct ath10k {TYPE_3__ wmi; TYPE_2__* running_fw; int /*<<< orphan*/  radar_confirmation_work; int /*<<< orphan*/  svc_rdy_work; void* wmi_key_cipher; } ;
struct TYPE_4__ {int wmi_op_version; int /*<<< orphan*/  fw_features; } ;
struct TYPE_5__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_MGMT_TX_BY_REF ; 
#define  ATH10K_FW_WMI_OP_VERSION_10_1 135 
#define  ATH10K_FW_WMI_OP_VERSION_10_2 134 
#define  ATH10K_FW_WMI_OP_VERSION_10_2_4 133 
#define  ATH10K_FW_WMI_OP_VERSION_10_4 132 
#define  ATH10K_FW_WMI_OP_VERSION_MAIN 131 
#define  ATH10K_FW_WMI_OP_VERSION_MAX 130 
#define  ATH10K_FW_WMI_OP_VERSION_TLV 129 
#define  ATH10K_FW_WMI_OP_VERSION_UNSET 128 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_radar_confirmation_work ; 
 int /*<<< orphan*/  ath10k_wmi_event_service_ready_work ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_attach (struct ath10k*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmi_10_1_ops ; 
 int /*<<< orphan*/  wmi_10_2_4_cmd_map ; 
 int /*<<< orphan*/  wmi_10_2_4_ops ; 
 int /*<<< orphan*/  wmi_10_2_4_pdev_param_map ; 
 int /*<<< orphan*/  wmi_10_2_4_vdev_param_map ; 
 int /*<<< orphan*/  wmi_10_2_cmd_map ; 
 int /*<<< orphan*/  wmi_10_2_ops ; 
 int /*<<< orphan*/  wmi_10_2_peer_flags_map ; 
 int /*<<< orphan*/  wmi_10_4_cmd_map ; 
 int /*<<< orphan*/  wmi_10_4_ops ; 
 int /*<<< orphan*/  wmi_10_4_pdev_param_map ; 
 int /*<<< orphan*/  wmi_10_4_vdev_param_map ; 
 int /*<<< orphan*/  wmi_10x_cmd_map ; 
 int /*<<< orphan*/  wmi_10x_pdev_param_map ; 
 int /*<<< orphan*/  wmi_10x_peer_flags_map ; 
 int /*<<< orphan*/  wmi_10x_vdev_param_map ; 
 int /*<<< orphan*/  wmi_cmd_map ; 
 void* wmi_key_cipher_suites ; 
 int /*<<< orphan*/  wmi_ops ; 
 int /*<<< orphan*/  wmi_pdev_param_map ; 
 int /*<<< orphan*/  wmi_peer_flags_map ; 
 void* wmi_tlv_key_cipher_suites ; 
 int /*<<< orphan*/  wmi_vdev_param_map ; 

int ath10k_wmi_attach(struct ath10k *ar)
{
	switch (ar->running_fw->fw_file.wmi_op_version) {
	case ATH10K_FW_WMI_OP_VERSION_10_4:
		ar->wmi.ops = &wmi_10_4_ops;
		ar->wmi.cmd = &wmi_10_4_cmd_map;
		ar->wmi.vdev_param = &wmi_10_4_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10_4_pdev_param_map;
		ar->wmi.peer_flags = &wmi_10_2_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		break;
	case ATH10K_FW_WMI_OP_VERSION_10_2_4:
		ar->wmi.cmd = &wmi_10_2_4_cmd_map;
		ar->wmi.ops = &wmi_10_2_4_ops;
		ar->wmi.vdev_param = &wmi_10_2_4_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10_2_4_pdev_param_map;
		ar->wmi.peer_flags = &wmi_10_2_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		break;
	case ATH10K_FW_WMI_OP_VERSION_10_2:
		ar->wmi.cmd = &wmi_10_2_cmd_map;
		ar->wmi.ops = &wmi_10_2_ops;
		ar->wmi.vdev_param = &wmi_10x_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10x_pdev_param_map;
		ar->wmi.peer_flags = &wmi_10_2_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		break;
	case ATH10K_FW_WMI_OP_VERSION_10_1:
		ar->wmi.cmd = &wmi_10x_cmd_map;
		ar->wmi.ops = &wmi_10_1_ops;
		ar->wmi.vdev_param = &wmi_10x_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10x_pdev_param_map;
		ar->wmi.peer_flags = &wmi_10x_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		break;
	case ATH10K_FW_WMI_OP_VERSION_MAIN:
		ar->wmi.cmd = &wmi_cmd_map;
		ar->wmi.ops = &wmi_ops;
		ar->wmi.vdev_param = &wmi_vdev_param_map;
		ar->wmi.pdev_param = &wmi_pdev_param_map;
		ar->wmi.peer_flags = &wmi_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		break;
	case ATH10K_FW_WMI_OP_VERSION_TLV:
		ath10k_wmi_tlv_attach(ar);
		ar->wmi_key_cipher = wmi_tlv_key_cipher_suites;
		break;
	case ATH10K_FW_WMI_OP_VERSION_UNSET:
	case ATH10K_FW_WMI_OP_VERSION_MAX:
		ath10k_err(ar, "unsupported WMI op version: %d\n",
			   ar->running_fw->fw_file.wmi_op_version);
		return -EINVAL;
	}

	init_completion(&ar->wmi.service_ready);
	init_completion(&ar->wmi.unified_ready);
	init_completion(&ar->wmi.barrier);
	init_completion(&ar->wmi.radar_confirm);

	INIT_WORK(&ar->svc_rdy_work, ath10k_wmi_event_service_ready_work);
	INIT_WORK(&ar->radar_confirmation_work,
		  ath10k_radar_confirmation_work);

	if (test_bit(ATH10K_FW_FEATURE_MGMT_TX_BY_REF,
		     ar->running_fw->fw_file.fw_features)) {
		idr_init(&ar->wmi.mgmt_pending_tx);
	}

	return 0;
}