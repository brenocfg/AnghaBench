#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_mvm_reprobe {int /*<<< orphan*/  work; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {scalar_t__ fw_restart; int /*<<< orphan*/  hw; int /*<<< orphan*/  status; TYPE_4__ fwrt; TYPE_3__* trans; int /*<<< orphan*/ * error_recovery_buf; TYPE_2__* fw; scalar_t__ hw_registered; int /*<<< orphan*/  notif_wait; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int error_log_size; int error_log_addr; } ;
struct TYPE_7__ {TYPE_1__ ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RESTART_REQUESTED ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  STATUS_TRANS_DEAD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ieee80211_restart_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_abort_notification_waits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_del_timers (TYPE_3__*) ; 
 int /*<<< orphan*/  iwl_fw_error_collect (TYPE_4__*) ; 
 int /*<<< orphan*/  iwl_mvm_report_scan_aborted (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_reprobe_wk ; 
 int /*<<< orphan*/  iwl_trans_read_mem_bytes (TYPE_3__*,int,int /*<<< orphan*/ *,int) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

void iwl_mvm_nic_restart(struct iwl_mvm *mvm, bool fw_error)
{
	iwl_abort_notification_waits(&mvm->notif_wait);
	iwl_dbg_tlv_del_timers(mvm->trans);

	/*
	 * This is a bit racy, but worst case we tell mac80211 about
	 * a stopped/aborted scan when that was already done which
	 * is not a problem. It is necessary to abort any os scan
	 * here because mac80211 requires having the scan cleared
	 * before restarting.
	 * We'll reset the scan_status to NONE in restart cleanup in
	 * the next start() call from mac80211. If restart isn't called
	 * (no fw restart) scan status will stay busy.
	 */
	iwl_mvm_report_scan_aborted(mvm);

	/*
	 * If we're restarting already, don't cycle restarts.
	 * If INIT fw asserted, it will likely fail again.
	 * If WoWLAN fw asserted, don't restart either, mac80211
	 * can't recover this since we're already half suspended.
	 */
	if (!mvm->fw_restart && fw_error) {
		iwl_fw_error_collect(&mvm->fwrt);
	} else if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) {
		struct iwl_mvm_reprobe *reprobe;

		IWL_ERR(mvm,
			"Firmware error during reconfiguration - reprobe!\n");

		/*
		 * get a module reference to avoid doing this while unloading
		 * anyway and to avoid scheduling a work with code that's
		 * being removed.
		 */
		if (!try_module_get(THIS_MODULE)) {
			IWL_ERR(mvm, "Module is being unloaded - abort\n");
			return;
		}

		reprobe = kzalloc(sizeof(*reprobe), GFP_ATOMIC);
		if (!reprobe) {
			module_put(THIS_MODULE);
			return;
		}
		reprobe->dev = mvm->trans->dev;
		INIT_WORK(&reprobe->work, iwl_mvm_reprobe_wk);
		schedule_work(&reprobe->work);
	} else if (test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
			    &mvm->status)) {
		IWL_ERR(mvm, "HW restart already requested, but not started\n");
	} else if (mvm->fwrt.cur_fw_img == IWL_UCODE_REGULAR &&
		   mvm->hw_registered &&
		   !test_bit(STATUS_TRANS_DEAD, &mvm->trans->status)) {
		if (mvm->fw->ucode_capa.error_log_size) {
			u32 src_size = mvm->fw->ucode_capa.error_log_size;
			u32 src_addr = mvm->fw->ucode_capa.error_log_addr;
			u8 *recover_buf = kzalloc(src_size, GFP_ATOMIC);

			if (recover_buf) {
				mvm->error_recovery_buf = recover_buf;
				iwl_trans_read_mem_bytes(mvm->trans,
							 src_addr,
							 recover_buf,
							 src_size);
			}
		}

		iwl_fw_error_collect(&mvm->fwrt);

		if (fw_error && mvm->fw_restart > 0)
			mvm->fw_restart--;
		set_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);
		ieee80211_restart_hw(mvm->hw);
	}
}