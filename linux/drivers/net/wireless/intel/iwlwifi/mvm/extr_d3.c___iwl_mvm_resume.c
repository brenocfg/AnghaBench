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
struct iwl_mvm {int /*<<< orphan*/  status; int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; struct ieee80211_vif* keep_vif; scalar_t__ net_detect; TYPE_2__* trans; int /*<<< orphan*/  fwrt; TYPE_1__* fw; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum iwl_d3_status { ____Placeholder_iwl_d3_status } iwl_d3_status ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  D0I3_END_CMD ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_vif*) ; 
 int IWL_D3_STATUS_ALIVE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_SCAN_NETDETECT ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RESTART_REQUESTED ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_D0I3_END_FIRST ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_rtnl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_dump_desc_assert ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_read_d3_debug_data (int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_mvm_check_rt_status (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_d3_disconnect_iter ; 
 int /*<<< orphan*/  iwl_mvm_dump_nic_error_log (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_free_nd (struct iwl_mvm*) ; 
 struct ieee80211_vif* iwl_mvm_get_bss_vif (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_ppag_send_cmd (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_query_netdetect_reasons (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_query_wakeup_reasons (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_sar_select_profile (struct iwl_mvm*,int,int) ; 
 int iwl_mvm_scan_stop (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_update_changed_regdom (struct iwl_mvm*) ; 
 int iwl_trans_d3_resume (TYPE_2__*,int*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __iwl_mvm_resume(struct iwl_mvm *mvm, bool test)
{
	struct ieee80211_vif *vif = NULL;
	int ret = 1;
	enum iwl_d3_status d3_status;
	bool keep = false;
	bool unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);
	bool d0i3_first = fw_has_capa(&mvm->fw->ucode_capa,
				      IWL_UCODE_TLV_CAPA_D0I3_END_FIRST);

	mutex_lock(&mvm->mutex);

	/* get the BSS vif pointer again */
	vif = iwl_mvm_get_bss_vif(mvm);
	if (IS_ERR_OR_NULL(vif))
		goto err;

	iwl_fw_dbg_read_d3_debug_data(&mvm->fwrt);

	if (iwl_mvm_check_rt_status(mvm, vif)) {
		set_bit(STATUS_FW_ERROR, &mvm->trans->status);
		iwl_mvm_dump_nic_error_log(mvm);
		iwl_fw_dbg_collect_desc(&mvm->fwrt, &iwl_dump_desc_assert,
					false, 0);
		ret = 1;
		goto err;
	}

	ret = iwl_trans_d3_resume(mvm->trans, &d3_status, test, !unified_image);
	if (ret)
		goto err;

	if (d3_status != IWL_D3_STATUS_ALIVE) {
		IWL_INFO(mvm, "Device was reset during suspend\n");
		goto err;
	}

	if (d0i3_first) {
		ret = iwl_mvm_send_cmd_pdu(mvm, D0I3_END_CMD, 0, 0, NULL);
		if (ret < 0) {
			IWL_ERR(mvm, "Failed to send D0I3_END_CMD first (%d)\n",
				ret);
			goto err;
		}
	}

	/*
	 * Query the current location and source from the D3 firmware so we
	 * can play it back when we re-intiailize the D0 firmware
	 */
	iwl_mvm_update_changed_regdom(mvm);

	/* Re-configure PPAG settings */
	iwl_mvm_ppag_send_cmd(mvm);

	if (!unified_image)
		/*  Re-configure default SAR profile */
		iwl_mvm_sar_select_profile(mvm, 1, 1);

	if (mvm->net_detect) {
		/* If this is a non-unified image, we restart the FW,
		 * so no need to stop the netdetect scan.  If that
		 * fails, continue and try to get the wake-up reasons,
		 * but trigger a HW restart by keeping a failure code
		 * in ret.
		 */
		if (unified_image)
			ret = iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_NETDETECT,
						false);

		iwl_mvm_query_netdetect_reasons(mvm, vif);
		/* has unlocked the mutex, so skip that */
		goto out;
	} else {
		keep = iwl_mvm_query_wakeup_reasons(mvm, vif);
#ifdef CONFIG_IWLWIFI_DEBUGFS
		if (keep)
			mvm->keep_vif = vif;
#endif
		/* has unlocked the mutex, so skip that */
		goto out_iterate;
	}

err:
	iwl_mvm_free_nd(mvm);
	mutex_unlock(&mvm->mutex);

out_iterate:
	if (!test)
		ieee80211_iterate_active_interfaces_rtnl(mvm->hw,
			IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_d3_disconnect_iter, keep ? vif : NULL);

out:
	/* no need to reset the device in unified images, if successful */
	if (unified_image && !ret) {
		/* nothing else to do if we already sent D0I3_END_CMD */
		if (d0i3_first)
			return 0;

		ret = iwl_mvm_send_cmd_pdu(mvm, D0I3_END_CMD, 0, 0, NULL);
		if (!ret)
			return 0;
	}

	/*
	 * Reconfigure the device in one of the following cases:
	 * 1. We are not using a unified image
	 * 2. We are using a unified image but had an error while exiting D3
	 */
	set_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);

	return 1;
}