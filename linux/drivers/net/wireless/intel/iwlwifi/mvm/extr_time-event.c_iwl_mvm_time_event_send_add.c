#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_time_event_cmd {int /*<<< orphan*/  id; int /*<<< orphan*/  duration; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm_time_event_data {scalar_t__ id; int /*<<< orphan*/  list; void* duration; struct ieee80211_vif* vif; } ;
struct iwl_mvm {int /*<<< orphan*/  time_event_lock; int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  time_event_list; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_TE (struct iwl_mvm*,char*,void*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 scalar_t__ TE_MAX ; 
#define  TIME_EVENT_CMD 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_time_event_data*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,struct iwl_time_event_cmd*) ; 
 int /*<<< orphan*/  iwl_mvm_te_clear_data (struct iwl_mvm*,struct iwl_mvm_time_event_data*) ; 
 int /*<<< orphan*/  iwl_mvm_time_event_response ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_time_event_send_add(struct iwl_mvm *mvm,
				       struct ieee80211_vif *vif,
				       struct iwl_mvm_time_event_data *te_data,
				       struct iwl_time_event_cmd *te_cmd)
{
	static const u16 time_event_response[] = { TIME_EVENT_CMD };
	struct iwl_notification_wait wait_time_event;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	IWL_DEBUG_TE(mvm, "Add new TE, duration %d TU\n",
		     le32_to_cpu(te_cmd->duration));

	spin_lock_bh(&mvm->time_event_lock);
	if (WARN_ON(te_data->id != TE_MAX)) {
		spin_unlock_bh(&mvm->time_event_lock);
		return -EIO;
	}
	te_data->vif = vif;
	te_data->duration = le32_to_cpu(te_cmd->duration);
	te_data->id = le32_to_cpu(te_cmd->id);
	list_add_tail(&te_data->list, &mvm->time_event_list);
	spin_unlock_bh(&mvm->time_event_lock);

	/*
	 * Use a notification wait, which really just processes the
	 * command response and doesn't wait for anything, in order
	 * to be able to process the response and get the UID inside
	 * the RX path. Using CMD_WANT_SKB doesn't work because it
	 * stores the buffer and then wakes up this thread, by which
	 * time another notification (that the time event started)
	 * might already be processed unsuccessfully.
	 */
	iwl_init_notification_wait(&mvm->notif_wait, &wait_time_event,
				   time_event_response,
				   ARRAY_SIZE(time_event_response),
				   iwl_mvm_time_event_response, te_data);

	ret = iwl_mvm_send_cmd_pdu(mvm, TIME_EVENT_CMD, 0,
					    sizeof(*te_cmd), te_cmd);
	if (ret) {
		IWL_ERR(mvm, "Couldn't send TIME_EVENT_CMD: %d\n", ret);
		iwl_remove_notification(&mvm->notif_wait, &wait_time_event);
		goto out_clear_te;
	}

	/* No need to wait for anything, so just pass 1 (0 isn't valid) */
	ret = iwl_wait_notification(&mvm->notif_wait, &wait_time_event, 1);
	/* should never fail */
	WARN_ON_ONCE(ret);

	if (ret) {
 out_clear_te:
		spin_lock_bh(&mvm->time_event_lock);
		iwl_mvm_te_clear_data(mvm, te_data);
		spin_unlock_bh(&mvm->time_event_lock);
	}
	return ret;
}