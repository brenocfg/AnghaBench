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
struct iwl_time_event_notif {int unique_id; int action; int status; } ;
struct iwl_mvm_time_event_data {int end_jiffies; int running; scalar_t__ id; TYPE_1__* vif; int /*<<< orphan*/  duration; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  status; int /*<<< orphan*/  time_event_lock; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TE (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_NEED_FLUSH_P2P ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_RUNNING ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
#define  NL80211_IFTYPE_P2P_DEVICE 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ TE_CHANNEL_SWITCH_PERIOD ; 
 int TE_V2_NOTIF_HOST_EVENT_END ; 
 int TE_V2_NOTIF_HOST_EVENT_START ; 
 int TU_TO_EXP_TIME (int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ieee80211_ready_on_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_remain_on_channel_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_roc_finished (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_te_check_disconnect (struct iwl_mvm*,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  iwl_mvm_te_check_trigger (struct iwl_mvm*,struct iwl_time_event_notif*,struct iwl_mvm_time_event_data*) ; 
 int /*<<< orphan*/  iwl_mvm_te_clear_data (struct iwl_mvm*,struct iwl_mvm_time_event_data*) ; 
 int /*<<< orphan*/  iwl_mvm_te_handle_notify_csa (struct iwl_mvm*,struct iwl_mvm_time_event_data*,struct iwl_time_event_notif*) ; 
 int jiffies ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_te_handle_notif(struct iwl_mvm *mvm,
				    struct iwl_mvm_time_event_data *te_data,
				    struct iwl_time_event_notif *notif)
{
	lockdep_assert_held(&mvm->time_event_lock);

	IWL_DEBUG_TE(mvm, "Handle time event notif - UID = 0x%x action %d\n",
		     le32_to_cpu(notif->unique_id),
		     le32_to_cpu(notif->action));

	iwl_mvm_te_check_trigger(mvm, notif, te_data);

	/*
	 * The FW sends the start/end time event notifications even for events
	 * that it fails to schedule. This is indicated in the status field of
	 * the notification. This happens in cases that the scheduler cannot
	 * find a schedule that can handle the event (for example requesting a
	 * P2P Device discoveribility, while there are other higher priority
	 * events in the system).
	 */
	if (!le32_to_cpu(notif->status)) {
		const char *msg;

		if (notif->action & cpu_to_le32(TE_V2_NOTIF_HOST_EVENT_START))
			msg = "Time Event start notification failure";
		else
			msg = "Time Event end notification failure";

		IWL_DEBUG_TE(mvm, "%s\n", msg);

		if (iwl_mvm_te_check_disconnect(mvm, te_data->vif, msg)) {
			iwl_mvm_te_clear_data(mvm, te_data);
			return;
		}
	}

	if (le32_to_cpu(notif->action) & TE_V2_NOTIF_HOST_EVENT_END) {
		IWL_DEBUG_TE(mvm,
			     "TE ended - current time %lu, estimated end %lu\n",
			     jiffies, te_data->end_jiffies);

		switch (te_data->vif->type) {
		case NL80211_IFTYPE_P2P_DEVICE:
			ieee80211_remain_on_channel_expired(mvm->hw);
			set_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status);
			iwl_mvm_roc_finished(mvm);
			break;
		case NL80211_IFTYPE_STATION:
			/*
			 * By now, we should have finished association
			 * and know the dtim period.
			 */
			iwl_mvm_te_check_disconnect(mvm, te_data->vif,
				"No beacon heard and the time event is over already...");
			break;
		default:
			break;
		}

		iwl_mvm_te_clear_data(mvm, te_data);
	} else if (le32_to_cpu(notif->action) & TE_V2_NOTIF_HOST_EVENT_START) {
		te_data->running = true;
		te_data->end_jiffies = TU_TO_EXP_TIME(te_data->duration);

		if (te_data->vif->type == NL80211_IFTYPE_P2P_DEVICE) {
			set_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status);
			ieee80211_ready_on_channel(mvm->hw);
		} else if (te_data->id == TE_CHANNEL_SWITCH_PERIOD) {
			iwl_mvm_te_handle_notify_csa(mvm, te_data, notif);
		}
	} else {
		IWL_WARN(mvm, "Got TE with unknown action\n");
	}
}