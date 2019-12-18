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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_periodic_scan_complete {scalar_t__ status; scalar_t__ ebs_status; int /*<<< orphan*/  time_after_last_iter; int /*<<< orphan*/  last_schedule_iteration; int /*<<< orphan*/  last_schedule_line; } ;
struct iwl_mvm {int scan_status; int last_ebs_successful; int /*<<< orphan*/  scan_timeout_dwork; int /*<<< orphan*/  hw; int /*<<< orphan*/  sched_scan_pass_all; int /*<<< orphan*/  mutex; TYPE_1__* fw; } ;
struct cfg80211_scan_info {int aborted; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int IWL_MVM_SCAN_REGULAR ; 
 int IWL_MVM_SCAN_SCHED ; 
 int IWL_MVM_SCAN_STOPPING_REGULAR ; 
 int IWL_MVM_SCAN_STOPPING_SCHED ; 
 scalar_t__ IWL_SCAN_EBS_INACTIVE ; 
 scalar_t__ IWL_SCAN_EBS_SUCCESS ; 
 scalar_t__ IWL_SCAN_OFFLOAD_ABORTED ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
 int /*<<< orphan*/  SCHED_SCAN_PASS_ALL_DISABLED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  ieee80211_sched_scan_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_ebs_status_str (scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_resume_tcm (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_lmac_scan_complete_notif(struct iwl_mvm *mvm,
					 struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_periodic_scan_complete *scan_notif = (void *)pkt->data;
	bool aborted = (scan_notif->status == IWL_SCAN_OFFLOAD_ABORTED);

	/* If this happens, the firmware has mistakenly sent an LMAC
	 * notification during UMAC scans -- warn and ignore it.
	 */
	if (WARN_ON_ONCE(fw_has_capa(&mvm->fw->ucode_capa,
				     IWL_UCODE_TLV_CAPA_UMAC_SCAN)))
		return;

	/* scan status must be locked for proper checking */
	lockdep_assert_held(&mvm->mutex);

	/* We first check if we were stopping a scan, in which case we
	 * just clear the stopping flag.  Then we check if it was a
	 * firmware initiated stop, in which case we need to inform
	 * mac80211.
	 * Note that we can have a stopping and a running scan
	 * simultaneously, but we can't have two different types of
	 * scans stopping or running at the same time (since LMAC
	 * doesn't support it).
	 */

	if (mvm->scan_status & IWL_MVM_SCAN_STOPPING_SCHED) {
		WARN_ON_ONCE(mvm->scan_status & IWL_MVM_SCAN_STOPPING_REGULAR);

		IWL_DEBUG_SCAN(mvm, "Scheduled scan %s, EBS status %s\n",
			       aborted ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notif->ebs_status));
		IWL_DEBUG_SCAN(mvm,
			       "Last line %d, Last iteration %d, Time after last iteration %d\n",
			       scan_notif->last_schedule_line,
			       scan_notif->last_schedule_iteration,
			       __le32_to_cpu(scan_notif->time_after_last_iter));

		mvm->scan_status &= ~IWL_MVM_SCAN_STOPPING_SCHED;
	} else if (mvm->scan_status & IWL_MVM_SCAN_STOPPING_REGULAR) {
		IWL_DEBUG_SCAN(mvm, "Regular scan %s, EBS status %s\n",
			       aborted ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notif->ebs_status));

		mvm->scan_status &= ~IWL_MVM_SCAN_STOPPING_REGULAR;
	} else if (mvm->scan_status & IWL_MVM_SCAN_SCHED) {
		WARN_ON_ONCE(mvm->scan_status & IWL_MVM_SCAN_REGULAR);

		IWL_DEBUG_SCAN(mvm, "Scheduled scan %s, EBS status %s\n",
			       aborted ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notif->ebs_status));
		IWL_DEBUG_SCAN(mvm,
			       "Last line %d, Last iteration %d, Time after last iteration %d (FW)\n",
			       scan_notif->last_schedule_line,
			       scan_notif->last_schedule_iteration,
			       __le32_to_cpu(scan_notif->time_after_last_iter));

		mvm->scan_status &= ~IWL_MVM_SCAN_SCHED;
		ieee80211_sched_scan_stopped(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
	} else if (mvm->scan_status & IWL_MVM_SCAN_REGULAR) {
		struct cfg80211_scan_info info = {
			.aborted = aborted,
		};

		IWL_DEBUG_SCAN(mvm, "Regular scan %s, EBS status %s (FW)\n",
			       aborted ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notif->ebs_status));

		mvm->scan_status &= ~IWL_MVM_SCAN_REGULAR;
		ieee80211_scan_completed(mvm->hw, &info);
		cancel_delayed_work(&mvm->scan_timeout_dwork);
		iwl_mvm_resume_tcm(mvm);
	} else {
		IWL_ERR(mvm,
			"got scan complete notification but no scan is running\n");
	}

	mvm->last_ebs_successful =
			scan_notif->ebs_status == IWL_SCAN_EBS_SUCCESS ||
			scan_notif->ebs_status == IWL_SCAN_EBS_INACTIVE;
}